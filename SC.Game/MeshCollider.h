#pragma once

namespace SC::Game
{
	/// <summary>
	/// 메쉬 형태의 충돌체를 나타냅니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class MeshCollider sealed : public Collider
	{
	internal:
		physx::PxConvexMesh* mConvexMesh = nullptr;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="MeshCollider"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		MeshCollider();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;
	};
}