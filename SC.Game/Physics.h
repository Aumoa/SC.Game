#pragma once

namespace SC::Game
{
	/// <summary>
	/// �������� ���� ��鿡 ���� ���� ������ �����ϴ� �Լ��� �����մϴ�.
	/// </summary>
	public ref class Physics
	{
	internal:
		static physx::PxFoundation* mFoundation;
		static physx::PxPvd* mPVD;
		static physx::PxPvdTransport* mPVDTransport;
		
		static physx::PxPhysics* mPhysics;
		static physx::PxCooking* mCooking;

		static physx::PxDefaultCpuDispatcher* mDispatcher;
		static physx::PxCudaContextManager* mCudaManager;

		static physx::PxMaterial* mDefaultMat;

	internal:
		static void OnDisposing();
		static void Initialize();

	public:
		/// <summary>
		/// ���� ���� ���� ��鿡�� ���� ������ �ǽ��մϴ�.
		/// </summary>
		/// <param name="ray"> ���� ������ �����մϴ�. </param>
		/// <param name="tag"> �浹�� ���͸��� �±׸� �����մϴ�. </param>
		/// <param name="exactly"> ���͸� �±װ� ��Ȯ�� ��ġ�ؾ� ���� ��Ÿ���ϴ�. </param>
		static RaycastHit RayCast( Ray ray, Tag tag, bool exactly );

		/// <summary>
		/// ���� ���� ���� ��鿡�� ���� ������ �ǽ��մϴ�.
		/// </summary>
		/// <param name="ray"> ���� ������ �����մϴ�. </param>
		static RaycastHit RayCast( Ray ray )
		{
			return RayCast( ray, Tag::All, false );
		}
	};
}