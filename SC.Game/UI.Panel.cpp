using namespace SC;
using namespace SC::Game::UI;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

using namespace std;

void Panel::Render( CDeviceContext& deviceContext )
{
	std::map<int, std::vector<gcroot<Element^>>> ordered_elements;

	for ( int i = 0; i < Count; ++i )
	{
		DependencyObject::Items^ items;
		int order = 0;

		if ( mContentType[i]->mProperties->TryGetValue( ClassName, items ) )
		{
			String^ value;

			if ( items->TryGetValue( ZOrder, value ) )
			{
				Int32::TryParse( value, order );
			}
		}

		ordered_elements[order].push_back( mContentType[i] );
	}

	for ( auto& i : ordered_elements )
	{
		for ( auto& j : i.second )
		{
			j->Render( deviceContext );
		}
	}
}

System::Collections::IEnumerator^ Panel::GetEnumerator2()
{
	return mContentType->GetEnumerator();
}

RectangleF Panel::OnUpdate( RectangleF clientRect )
{
	for each ( auto item in this )
	{
		item->Update( clientRect );
	}

	return clientRect;
}

Panel::Panel( String^ xName ) : Element( xName )
{
	mContentType = gcnew ContentType();
	Content = mContentType;
}

IEnumerator<Element^>^ Panel::GetEnumerator()
{
	return mContentType->GetEnumerator();
}

void Panel::Add( Element^ value )
{
	mContentType->Add( value );
}

void Panel::Clear()
{
	mContentType->Clear();
}

bool Panel::Contains( Element^ value )
{
	return mContentType->Contains( value );
}

void Panel::CopyTo( cli::array<Element^>^ array, int index )
{
	mContentType->CopyTo( array, index );
}

int Panel::IndexOf( Element^ value )
{
	return mContentType->IndexOf( value );
}

void Panel::Insert( int index, Element^ value )
{
	mContentType->Insert( index, value );
}

bool Panel::Remove( Element^ value )
{
	return mContentType->Remove( value );
}

void Panel::RemoveAt( int index )
{
	mContentType->RemoveAt( index );
}

int Panel::IndexOf( String^ xName )
{
	int indexOf = 0;
	for each ( Element ^ elem in mContentType )
	{
		if ( elem->Name == xName ) return indexOf;
		else indexOf++;
	}

	return -1;
}

int Panel::Count::get()
{
	return mContentType->Count;
}

bool Panel::IsFixedSize::get()
{
	return false;
}

bool Panel::IsReadOnly::get()
{
	return false;
}

Element^ Panel::default::get( int index )
{
	return mContentType[index];
}

void Panel::default::set( int index, Element ^ value )
{
	mContentType[index] = value;
}