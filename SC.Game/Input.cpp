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