using namespace SC;
using namespace SC::Game::UI;

using namespace System;
using namespace System::Drawing;

std::function<void()> lambda;

Element::Element( String^ xName )
{
	mName = xName;
}

RectangleF Element::OnUpdate( RectangleF clientRect )
{
	if ( auto is = ( Element^ )mContent; is )
	{
		is->Update( clientRect );
	}

	return clientRect;
}

void Element::Render( CDeviceContext& deviceContext )
{
	if ( auto is = ( Element^ )mContent; is )
	{
		is->Render( deviceContext );
	}
}

String^ Element::ToString()
{
	return String::Format( "{0} xName: {1}", Object::ToString(), mName );
}

void Element::Update( RectangleF clientRect )
{
	clientRect.X += mMargin.Left;
	clientRect.Y += mMargin.Top;
	clientRect.Width -= mMargin.Width;
	clientRect.Height -= mMargin.Height;

	array<PointF>^ offset = gcnew array<PointF>
	{
		PointF( 0, 0 ), PointF( 0.5f, 0 ), PointF( 1.0f, 0 ),
		PointF( 0, 0.5f ), PointF( 0.5f, 0.5f ), PointF( 1.0f, 0.5f ),
		PointF( 0, 1.0f ), PointF( 0.5f, 1.0f ), PointF( 1.0f, 1.0f )
	};

	if ( Width != 0 )
	{
		auto right = clientRect.Right - Width;
		auto length = right - clientRect.Left;

		int idx = ( int )mAnchor;
		clientRect.X += offset[idx].X * length;
		clientRect.Width = Width;
	}

	if ( Height != 0 )
	{
		auto bottom = clientRect.Bottom - Height;
		auto length = bottom - clientRect.Top;

		int idx = ( int )mAnchor;
		clientRect.Y += offset[idx].Y * length;
		clientRect.Height = Height;
	}

	clientRect = OnUpdate( clientRect );
	mActualRenderingRect = clientRect;
}

Thickness Element::Margin::get()
{
	return mMargin;
}

void Element::Margin::set( Thickness value )
{
	mMargin = value;
}

String^ Element::Name::get()
{
	return mName;
}

Object^ Element::Content::get()
{
	return mContent;
}

void Element::Content::set( Object^ value )
{
	mContent = value;
	ContentChanged( value );
}

float Element::Width::get()
{
	return mWidth;
}

void Element::Width::set( float value )
{
	mWidth = value;
}

float Element::Height::get()
{
	return mHeight;
}

void Element::Height::set( float value )
{
	mHeight = value;
}

Anchor Element::Anchor::get()
{
	return mAnchor;
}

void Element::Anchor::set( UI::Anchor value )
{
	mAnchor = value;
}

RectangleF Element::ActualRenderingRect::get()
{
	return mActualRenderingRect;
}