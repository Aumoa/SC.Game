using namespace SC;
using namespace SC::Game::UI;
using namespace SC::Game::UI::Shapes;

using namespace System;

Shape::Shape( String^ xName ) : Element( xName )
{
	mBrush = UISystem::mDefaultBlackBrush;
}

Brush^ Shape::Fill::get()
{
	return mBrush;
}

void Shape::Fill::set( Brush^ value )
{
	mBrush = value;
}