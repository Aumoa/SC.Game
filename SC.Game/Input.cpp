using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Drawing;

static Input::Input()
{
	mPrevKeyboardData = gcnew array<bool, 1>( 256 );
	mKeyboardData = gcnew array<bool, 1>( 256 );
}

void Input::Update()
{
	// �ý��ۿ��� Ŀ���� ��ġ�� �����ɴϴ�.
	POINT point;
	GetCursorPos( &point );

	// ȭ�� ���� ��ǥ���� â ���� ��ǥ�� ��ȯ�մϴ�.
	ScreenToClient( App::hWnd, &point );

	// �� ��ǥ�� ����մϴ�.
	mCursorPos = Point( point.x, point.y );

	// ���� Ű���� ���¸� �����մϴ�. �����͸� �������� �ʰ� ���� ��ü�� Swap�մϴ�.
	auto l = mPrevKeyboardData;
	mPrevKeyboardData = mKeyboardData;
	mKeyboardData = l;

	// �ý��ۿ��� Ű���� �����͸� �ҷ��ɴϴ�.
	BYTE keyboardData[256];
	GetKeyboardState( ( PBYTE )keyboardData );

	// �� â�� Ȱ��ȭ �Ǿ����� ���� Ű �Է��� �����ɴϴ�.
	if ( GetActiveWindow() == App::hWnd )
	{
		BYTE vks[256];
		GetKeyboardState( vks );
		for ( int i = 0; i < 256; ++i )
		{
			mKeyboardData[i] = ( keyboardData[i] & 0x80 ) != 0;
		}
	}
}

void Input::LateUpdate()
{
	mScrollDelta = System::Drawing::PointF( 0, 0 );

	switch ( Cursor::mLockMode )
	{
	case CursorLockMode::Locked:
		RECT rect;
		GetClientRect( App::hWnd, &rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect );
		ClientToScreen( App::hWnd, ( POINT* )&rect + 1 );
		POINT point;
		point.x = ( rect.left + rect.right ) / 2;
		point.y = ( rect.top + rect.bottom ) / 2;
		SetCursorPos( point.x, point.y );

		break;
	}
}

bool Input::GetKeyDown( KeyCode keyCode )
{
	int index = ( int )keyCode;

	return mKeyboardData[index]
		&& !mPrevKeyboardData[index];
}

bool Input::GetKeyUp( KeyCode keyCode )
{
	int index = ( int )keyCode;

	return !mKeyboardData[index]
		&& mPrevKeyboardData[index];
}

bool Input::GetKey( KeyCode keyCode )
{
	int index = ( int )keyCode;

	return mKeyboardData[index];
}

Point Input::MousePosition::get()
{
	return mCursorPos;
}

PointF Input::MouseScrollDelta::get()
{
	return mScrollDelta;
}

Point Input::CenterMousePosition::get()
{
	RECT rect;
	GetClientRect( App::hWnd, &rect );
	auto width = rect.right - rect.left;
	auto height = rect.bottom - rect.top;
	POINT point;
	point.x = width / 2;
	point.y = height / 2;

	return Point( point.x, point.y );
}