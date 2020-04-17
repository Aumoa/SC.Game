#pragma once

namespace SC::Game
{
	ref class Material;

	/// <summary>
	/// ������Ʈ���� ������ �޽� ��ü�� ȭ�鿡 �������մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class SkinnedMeshRenderer sealed : public Component
	{
	internal:
		Mesh^ mMesh;
		Material^ mMaterial;

		LargeHeap* mVertexBuffer = nullptr;

	internal:
		void Skinning( CDeviceContext& deviceContext );
		void Render( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// <see cref="SkinnedMeshRenderer"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		SkinnedMeshRenderer();
		~SkinnedMeshRenderer();
		!SkinnedMeshRenderer();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// �ش� �޽� �������� ����� �޽� ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Mesh^ Mesh
		{
			Game::Mesh^ get();
			void set( Game::Mesh^ value );
		}

		/// <summary>
		/// �ش� �޽� �������� ����� ���� ��ü�� �����ϰų� �����ɴϴ�. Null�� ��� �⺻�� ������ ����մϴ�.
		/// </summary>
		property Material^ Material
		{
			Game::Material^ get();
			void set( Game::Material^ value );
		}
	};
}