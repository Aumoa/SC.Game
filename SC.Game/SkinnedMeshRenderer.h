#pragma once

namespace SC::Game
{
	ref class Material;

	/// <summary>
	/// 컴포넌트에서 지정된 메쉬 개체를 화면에 렌더링합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="SkinnedMeshRenderer"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		SkinnedMeshRenderer();
		~SkinnedMeshRenderer();
		!SkinnedMeshRenderer();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 해당 메쉬 렌더러가 사용할 메쉬 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Mesh^ Mesh
		{
			Game::Mesh^ get();
			void set( Game::Mesh^ value );
		}

		/// <summary>
		/// 해당 메쉬 렌더러가 사용할 재질 개체를 설정하거나 가져옵니다. Null일 경우 기본값 재질을 사용합니다.
		/// </summary>
		property Material^ Material
		{
			Game::Material^ get();
			void set( Game::Material^ value );
		}
	};
}