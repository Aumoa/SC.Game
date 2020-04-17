using namespace SC;
using namespace SC::Game;

using namespace System;

ComponentDisconnectedException::ComponentDisconnectedException( Object^ sender ) : Exception( String::Format( L"컴포넌트가 사용되었지만 게임 개체와 연결되지 않았거나 연결이 종료되었습니다.\n사용한 개체: {0}", sender ) )
{

}