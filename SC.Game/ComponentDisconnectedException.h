#pragma once

namespace SC::Game
{
	/// <summary>
	/// ������Ʈ�� ���Ǿ����� ���� ��ü�� ������� �ʾҰų� ������ ����Ǿ��� ��� �߻��ϴ� �����Դϴ�.
	/// </summary>
	public ref class ComponentDisconnectedException : public System::Exception
	{
	public:
		/// <summary>
		/// �⺻ ���� �޽����� ����Ͽ� <see cref="ComponentDisconnectedException"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		ComponentDisconnectedException( System::Object^ sender );
	};
}