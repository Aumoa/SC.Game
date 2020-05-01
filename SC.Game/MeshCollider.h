#pragma once

namespace SC::Game
{
	/// <summary>
	/// �޽� ������ �浹ü�� ��Ÿ���ϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class MeshCollider sealed : public Collider
	{
	internal:
		physx::PxConvexMesh* mConvexMesh = nullptr;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="MeshCollider"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		MeshCollider();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;
	};
}