using namespace SC;
using namespace SC::Game::UI;

using namespace std;

using namespace System;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Threading;

using System::Drawing::RectangleF;

void TextBlock::Render( CDeviceContext& deviceContext )
{
	auto lock = mMutex->Lock();

	if ( mLayout )
	{
		auto rect = mComputed;
		HR( mLayout->Draw( &deviceContext, mGlyphRenderer, rect.Left, rect.Top ) );
	}
}

RectangleF TextBlock::OnUpdate( RectangleF clientRect )
{
	if ( ( clientRect != mPrevClient || mContentChanged ) && mLayout )
	{
		auto lock = mMutex->Lock();

		mPrevClient = clientRect;
		mComputed = clientRect;

		HR( mLayout->SetMaxWidth( ( float )mComputed.Width ) );
		HR( mLayout->SetMaxHeight( ( float )mComputed.Height ) );

		if ( Width == 0 && Height == 0 && mAutoSizing )
		{
			DWRITE_TEXT_METRICS metrics;
			HR( mLayout->GetMetrics( &metrics ) );

			auto actualWidth = metrics.width;
			auto actualHeight = metrics.height;

			auto offset = gcnew cli::array<PointF>( 9 )
			{
				PointF( 0, 0 ), PointF( 0.5f, 0 ), PointF( 1.0f, 0 ),
				PointF( 0, 0.5f ), PointF( 0.5f, 0.5f ), PointF( 1.0f, 0.5f ),
				PointF( 0, 1.0f ), PointF( 0.5f, 1.0f ), PointF( 1.0f, 1.0f )
			};

			auto right = mComputed.Right - actualWidth;
			auto length = right - mComputed.Left;

			int idx = ( int )Anchor;
			mComputed.X += offset[idx].X * length;
			mComputed.Width = actualWidth;

			auto bottom = mComputed.Bottom - actualHeight;
			length = bottom - mComputed.Top;

			idx = ( int )Anchor;
			mComputed.Y += offset[idx].Y * length;
			mComputed.Height = actualHeight;

			HR( mLayout->SetMaxWidth( ( float )mComputed.Width ) );
			HR( mLayout->SetMaxHeight( ( float )mComputed.Height ) );
		}

		mContentChanged = false;
	}

	return mComputed;
}

TextBlock::TextBlock( String^ xName ) : Element( xName )
{
	mMutex = new Mutex();

	ContentChanged += gcnew SC::Game::UI::ContentChangedDelegate( this, &TextBlock::OnContentChanged );
	mTextFormat = UISystem::mDefaultTextFormat;

	OnFormatChanged();
}

TextBlock::~TextBlock()
{
	this->!TextBlock();
}

TextBlock::!TextBlock()
{
	if ( mLayout )
	{
		mLayout->Release();
		mLayout = nullptr;
	}

	if ( mGlyphRenderer )
	{
		mGlyphRenderer->Release();
		mGlyphRenderer = nullptr;
	}

	if ( mMutex )
	{
		delete mMutex;
		mMutex = nullptr;
	}
}

TextFormat^ TextBlock::Format::get()
{
	return mTextFormat;
}

void TextBlock::Format::set( TextFormat^ value )
{
	mTextFormat = value;
	OnFormatChanged();
}

TextAlignment TextBlock::Alignment::get()
{
	return mTextAlignment;
}

void TextBlock::Alignment::set( TextAlignment value )
{
	DWRITE_TEXT_ALIGNMENT alignments[]
	{
		DWRITE_TEXT_ALIGNMENT_LEADING,
		DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_TEXT_ALIGNMENT_TRAILING,
		DWRITE_TEXT_ALIGNMENT_JUSTIFIED
	};

	if ( mLayout )
	{
		HR( mLayout->SetTextAlignment( alignments[( int )value] ) );
	}
	mTextAlignment = value;
}

TextVerticalAlignment TextBlock::VerticalAlignment::get()
{
	return mTextVerticalAlignment;
}

void TextBlock::VerticalAlignment::set( TextVerticalAlignment value )
{
	DWRITE_PARAGRAPH_ALIGNMENT alignments[]
	{
		DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_FAR
	};

	if ( mLayout )
	{
		HR( mLayout->SetParagraphAlignment( alignments[( int )value] ) );
	}
	mTextVerticalAlignment = value;
}

bool TextBlock::AutoSizing::get()
{
	return mAutoSizing;
}

void TextBlock::AutoSizing::set( bool value )
{
	mAutoSizing = value;
}

SC::Game::UI::Brush^ TextBlock::Fill::get()
{
	return mGlyphRenderer->mFillBrush;
}

void TextBlock::Fill::set( SC::Game::UI::Brush^ value )
{
	mGlyphRenderer->mFillBrush = value;
}

float TextBlock::Opacity::get()
{
	return mGlyphRenderer->mOpacity;
}

void TextBlock::Opacity::set( float value )
{
	mGlyphRenderer->mOpacity = value;
}

void TextBlock::OnFormatChanged()
{
	if ( mGlyphRenderer )
	{
		mGlyphRenderer->mGlyphBuffer = mTextFormat->mGlyphBuffer;
	}
	else
	{
		mGlyphRenderer = new GlyphRenderer( mTextFormat->mGlyphBuffer );
	}
	mPrevText = L"";
	OnContentChanged( Content );
}

void TextBlock::OnContentChanged( Object^ value )
{
	auto lock = mMutex->Lock();

	if ( value )
	{
		auto str = value->ToString();

		if ( str != mPrevText )
		{
			ParseText( str );

			Alignment = Alignment;
			VerticalAlignment = VerticalAlignment;
			mContentChanged = true;
			mPrevText = str;
		}
	}
}

void TextBlock::ParseText( String^ original )
{
	StringBuilder^ builder = gcnew StringBuilder();

	vector<pair<DWRITE_TEXT_RANGE, gcroot<Color>>> colorContexts;
	stack<pair<int, gcroot<Color>>> colorStack;

	vector<DWRITE_TEXT_RANGE> boldContexts;
	stack<int> boldStack;

	vector<DWRITE_TEXT_RANGE> underlineContexts;
	stack<int> underlineStack;

	vector<DWRITE_TEXT_RANGE> throughContexts;
	stack<int> throughStack;

	vector<DWRITE_TEXT_RANGE> italicContexts;
	stack<int> italicStack;

	int i = 0;
	while ( i < original->Length )
	{
		auto indexOf = original->IndexOf( L'<', i );

		// 문자열에 특수 컨텍스트가 없습니다.
		if ( indexOf == -1 )
		{
			builder->Append( original->Substring( i ) );
			break;
		}
		else
		{
			// 토큰 시작 전 문자열을 기록합니다.
			builder->Append( original->Substring( i, indexOf - i ) );

			// 토큰 종료 지점을 검색합니다.
			auto endOf = original->IndexOf( L'>', indexOf );

			// 문자열 파싱 에러입니다.
			if ( endOf == -1 )
			{
				builder->Append( original->Substring( i ) );

				return;
			}
			else
			{
				auto token = original->Substring( indexOf + 1, endOf - indexOf - 1 );

				//
				// 구문을 분석합니다.
				auto sep = token->IndexOf( L'=' );
				String^ key;
				String^ value;
				if ( sep == -1 )
				{
					key = token;
					value = "";
				}
				else
				{
					key = token->Substring( 0, sep );
					value = token->Substring( sep + 1, token->Length - sep - 1 );
				}

				//
				// 각 토큰에 대한 행동을 수행합니다.
				bool ret = false;
				if ( key->default[0] != L'/' )  // Close seq
				{
					stack<int>* stack = nullptr;

					if ( key == L"b" ) { stack = &boldStack; }
					else if ( key == L"u" ) { stack = &underlineStack; }
					else if ( key == L"t" ) { stack = &throughStack; }
					else if ( key == L"i" ) { stack = &italicStack; }
					else if ( key == L"color" )
					{
						auto pos = ( int )builder->Length;
						auto color = ColorTranslator::FromHtml( value );
						colorStack.push( { pos, gcroot<Color>( color ) } );
						ret = true;
					}
					else { ret = true; }

					if ( !ret )
					{
						stack->push( ( int )builder->Length );
					}
				}
				else
				{
					stack<int>* stack = nullptr;
					vector<DWRITE_TEXT_RANGE>* contexts = nullptr;

					if ( key == L"/b" )
					{
						stack = &boldStack;
						contexts = &boldContexts;
					}
					else if ( key == L"/u" )
					{
						stack = &underlineStack;
						contexts = &underlineContexts;
					}
					else if ( key == L"/t" )
					{
						stack = &throughStack;
						contexts = &throughContexts;
					}
					else if ( key == L"/color" )
					{
						auto c = colorStack.top();
						colorStack.pop();

						colorContexts.push_back( { { ( UINT )c.first, ( UINT )builder->Length - ( UINT )c.first }, c.second } );
						ret = true;
					}
					else
					{
						ret = true;
					}

					if ( !ret )
					{
						auto pos = stack->top();
						stack->pop();
						contexts->push_back( DWRITE_TEXT_RANGE{ ( UINT )pos, ( UINT )builder->Length - ( UINT )pos } );
					}
				}

				i = endOf + 1;
			}
		}
	}

	auto pDWriteFactory = Graphics::mFactory->pDWriteFactory.Get();
	auto str = builder->ToString();

	ComPtr<IDWriteTextLayout> pLayout;
	HR( pDWriteFactory->CreateTextLayout( msclr::interop::marshal_context().marshal_as<const wchar_t*>( str ), ( UINT32 )str->Length, mTextFormat->mTextFormat, 0, 0, &pLayout ) );
	pLayout->SetMaxWidth( ( float )mComputed.Width );
	pLayout->SetMaxHeight( ( float )mComputed.Height );

	for ( size_t i = 0; i < colorContexts.size(); ++i )
	{
		auto cont = colorContexts[i];
		HR( pLayout->SetDrawingEffect( new RichTextColorUnknown( gcnew SolidColorBrush( cont.second ) ), cont.first ) );
	}

	for ( size_t i = 0; i < boldContexts.size(); ++i )
	{
		auto cont = boldContexts[i];
		HR( pLayout->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD, cont ) );
	}

	for ( size_t i = 0; i < underlineContexts.size(); ++i )
	{
		auto cont = underlineContexts[i];
		HR( pLayout->SetUnderline( TRUE, cont ) );
	}

	for ( size_t i = 0; i < italicContexts.size(); ++i )
	{
		auto cont = italicContexts[i];
		HR( pLayout->SetFontStyle( DWRITE_FONT_STYLE_ITALIC, cont ) );
	}

	for ( size_t i = 0; i < throughContexts.size(); ++i )
	{
		auto cont = throughContexts[i];
		HR( pLayout->SetStrikethrough( TRUE, cont ) );
	}

	mLayout = pLayout.Detach();
}