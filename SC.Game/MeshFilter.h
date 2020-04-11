#pragma once

namespace SC::Game
{
	ref class Mesh;

	/// <summary>
	/// �޽� �����͸� ����ϴ� ������Ʈ���� �޽� �����͸� �����ϱ� ���� ���Ǵ� ������Ʈ�Դϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class MeshFilter sealed : public Component
	{
	internal:
		Mesh^ mMesh;

	public:
		/// <summary>
		/// <see cref="MeshFilter"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		MeshFilter();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// �ش� ������Ʈ�� �����ϴ� �޽� ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Mesh^ Mesh
		{
			Game::Mesh^ get();
			void set( Game::Mesh^ value );
		}
	};
}