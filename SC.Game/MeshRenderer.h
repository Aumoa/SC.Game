#pragma once

namespace SC::Game
{
	/// <summary>
	/// <see cref="MeshFilter"/> ������Ʈ���� ������ �޽� ��ü�� ȭ�鿡 �������մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class MeshRenderer : public Component
	{
	internal:
		void Render( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// <see cref="MeshRenderer"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		MeshRenderer();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;
	};
}