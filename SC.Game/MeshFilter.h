#pragma once

namespace SC::Game
{
	ref class Mesh;

	/// <summary>
	/// 메쉬 데이터를 사용하는 컴포넌트에서 메쉬 데이터를 참조하기 위해 사용되는 컴포넌트입니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class MeshFilter sealed : public Component
	{
	internal:
		Mesh^ mMesh;

	public:
		/// <summary>
		/// <see cref="MeshFilter"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		MeshFilter();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 해당 컴포넌트가 참조하는 메쉬 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Mesh^ Mesh
		{
			Game::Mesh^ get();
			void set( Game::Mesh^ value );
		}
	};
}