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
	// 시스템에서 커서의 위치를 가져옵니다.
	POINT point;
	GetCursorPos( &point );

	// 화면 공간 좌표에서 창 공간 좌표로 변환합니다.
	ScreenToClient( App::hWnd, &point );

	// 새 좌표를 등록합니다.
	mCursorPos = Point( point.x, point.y );

	// 이전 키보드 상태를 저장합니다. 데이터를 복사하지 않고 상태 개체를 Swap합니다.
	auto l = mPrevKeyboardData;
	mPrevKeyboardData = mKeyboardData;
	mKeyboardData = l;

	// 시스템에서 키보드 데이터를 불러옵니다.
	BYTE keyboardData[256];
	GetKeyboardState( ( PBYTE )keyboardData );

	// 주 창이 활성화 되어있을 때만 키 입력을 가져옵니다.
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