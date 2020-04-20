using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Drawing;

CursorLockMode Cursor::LockState::get()
{
	return mLockMode;
}

void Cursor::LockState::set( CursorLockMode value )
{
	mLockMode = value;

	switch ( mLockMode )
	{
	case CursorLockMode::Locked:
	{
		RECT rect;
		GetClientRect( App::hWnd, &rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect + 1 );
		POINT point;
		point.x = ( rect.left + rect.right ) / 2;
		point.y = ( rect.top + rect.bottom ) / 2;
		SetCursorPos( point.x, point.y );

		ScreenToClient( App::hWnd, &point );
		Input::mCursorPos = Point( point.x, point.y );
		break;
	}

	case CursorLockMode::Confined:
	{
		RECT rect;
		GetClientRect( App::hWnd, &rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect + 1 );

		ClipCursor( &rect );
		break;
	}

	case CursorLockMode::None:
		ClipCursor( nullptr );
		break;
	}
}

bool Cursor::Visible::get()
{
	return mVisible;
}

void Cursor::Visible::set( bool value )
{
	if ( value )
	{
		while ( mVisible <= 0 )
		{
			mVisible += 1;
			ShowCursor( TRUE );
		}
	}
	else if ( !value )
	{
		while ( mVisible >= 1 )
		{
			mVisible -= 1;
			ShowCursor( FALSE );
		}
	}
}