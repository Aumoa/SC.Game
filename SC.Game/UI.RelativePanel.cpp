using namespace SC;
using namespace SC::Game::UI;

using namespace System;

using System::Drawing::RectangleF;

RectangleF RelativePanel::OnUpdate( RectangleF clientRect )
{
	using namespace std;

	if ( Width != 0 || Height != 0 )
	{
		clientRect.Width = Width;
		clientRect.Height = Height;
	}

	vector<gcroot<RectangleF>> computedRects( Count, clientRect );
	vector<bool> computed( Count, false );

	for ( int i = 0; i < Count; ++i )
	{
		ComputeRect( i, computedRects, computed );
	}

	return clientRect;
}

RelativePanel::RelativePanel( String^ xName ) : Panel( xName )
{

}

void RelativePanel::ComputeRect( int index, std::vector<gcroot<RectangleF>>& computedRects, std::vector<bool>& computed )
{
	auto item = this[index];

	bool alignWithPanel[4] = { false };

	if ( computed[index] == false )
	{
		auto contentRect = ( RectangleF )computedRects[index];

		DependencyObject::Items^ items;

		if ( item->mProperties->TryGetValue( ClassName, items ) )
		{
			String^ value;

			if ( items->TryGetValue( Below, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto bottom = contentRect.Bottom;
					contentRect.Y = computed.Bottom;
					contentRect.Height = bottom - contentRect.Y;
				}
			}

			if ( items->TryGetValue( Above, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					contentRect.Height -= contentRect.Bottom - computed.Top;
				}
			}

			if ( items->TryGetValue( RightOf, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto right = contentRect.Right;
					contentRect.X = computed.Right;
					contentRect.Width = right - contentRect.X;
				}
			}

			if ( items->TryGetValue( LeftOf, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					contentRect.Width -= contentRect.Right - computed.Left;
				}
			}

			if ( items->TryGetValue( AlignLeftWith, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto delta = contentRect.Left - computed.Left;
					contentRect.X = computed.Left;
					contentRect.Width += delta;
				}
			}

			if ( items->TryGetValue( AlignTopWith, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto delta = contentRect.Top - computed.Top;
					contentRect.Y = computed.Top;
					contentRect.Height += delta;
				}
			}

			if ( items->TryGetValue( AlignRightWith, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto delta = contentRect.Right - computed.Right;
					contentRect.Width -= delta;
				}
			}

			if ( items->TryGetValue( AlignBottomWith, value ) )
			{
				int indexOf = IndexOf( value );
				if ( indexOf != -1 )
				{
					ComputeRect( indexOf, computedRects, computed );
					RectangleF computed = computedRects[indexOf];

					auto delta = contentRect.Bottom - computed.Bottom;
					contentRect.Height -= delta;
				}
			}
		}

		item->Update( contentRect );
		contentRect = item->ActualRenderingRect;

		computedRects[index] = contentRect;
		computed[index] = true;
	}
}