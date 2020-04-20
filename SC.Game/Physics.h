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
		static void Initialize();

	public:
		/// <summary>
		/// 현재 진행 중인 장면에서 광선 추적을 실시합니다.
		/// </summary>
		/// <param name="ray"> 광선 정보를 전달합니다. </param>
		/// <param name="tag"> 충돌을 필터링할 태그를 전달합니다. </param>
		/// <param name="exactly"> 필터링 태그가 정확히 일치해야 함을 나타냅니다. </param>
		static RaycastHit RayCast( Ray ray, Tag tag, bool exactly );

		/// <summary>
		/// 현재 진행 중인 장면에서 광선 추적을 실시합니다.
		/// </summary>
		/// <param name="ray"> 광선 정보를 전달합니다. </param>
		static RaycastHit RayCast( Ray ray )
		{
			return RayCast( ray, Tag::All, false );
		}
	};
}