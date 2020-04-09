using namespace SC;
using namespace SC::Game::UI;

using namespace System;
using namespace System::Collections::Generic;

DependencyObject::DependencyObject()
{
	mProperties = gcnew Classes();
}

void DependencyObject::AddDependencyProperty( DependencyProperty value )
{
	Items^ items;

	if ( mProperties->TryGetValue( value.ClassName, items ) )
	{
		items->Add( value.PropertyName, value.Value );
	}
	else
	{
		items = gcnew Items();
		items->Add( value.PropertyName, value.Value );
		mProperties->Add( value.ClassName, items );
	}
}

void DependencyObject::RemoveDependencyProperty( int className, int propertyName )
{
	Items^ items;

	if ( mProperties->TryGetValue( className, items ) )
	{
		items->Remove( propertyName );
		if ( items->Count == 0 )
		{
			mProperties->Remove( className );
		}
	}
}

void DependencyObject::RemoveDependencyProperty( int className )
{
	mProperties->Remove( className );
}