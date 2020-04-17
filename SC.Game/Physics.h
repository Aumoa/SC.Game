#pragma once

namespace SC::Game
{
	/// <summary>
	/// 엔진에서 현재 장면에 대한 물리 접근을 제어하는 함수를 제공합니다.
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