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

	public:
		static void Initialize();
	};
}