using namespace SC;
using namespace SC::Game;

using namespace System;

ComponentDisconnectedException::ComponentDisconnectedException( Object^ sender ) : Exception( String::Format( L"������Ʈ�� ���Ǿ����� ���� ��ü�� ������� �ʾҰų� ������ ����Ǿ����ϴ�.\n����� ��ü: {0}", sender ) )
{

}