#pragma once

namespace SC::Game
{
	/// <summary>
	/// 모든 충돌체(Collider)의 기본 클래스를 나타냅니다.
	/// </summary>
	public ref class Collider abstract : public Component
	{
	internal:
		System::Numerics::Vector3 mCenter = System::Numerics::Vector3::Zero;
		System::Numerics::Quaternion mRotation = System::Numerics::Quaternion::Identity;
		bool mIsTrigger = false;

		physx::PxRigidActor* mActor = nullptr;
		physx::PxShape* mShape = nullptr;

		physx::PxGeometry* mGeometry = nullptr;
		PhysicsMaterial^ mMaterial;
		bool mHasUpdate = false;
		bool mMaterialUpdated = true;

		Collider();

		void CloneAs( Collider^ pCollider );
		void AttachToActor( physx::PxRigidActor* pActor );
		virtual void Update();
		void ReleaseShape();

	public:
		~Collider();
		!Collider();

		/// <summary>
		/// 충돌체 모양의 중심을 나타내는 값을 설정하거나 가져옵니다. 개체의 로컬 좌표로 측정됩니다.
		/// </summary>
		property System::Numerics::Vector3 Center
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 충돌체 모양의 회전을 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// 이 충돌체가 이벤트를 발생시키는 트리거 충돌체임을 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property bool IsTrigger
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// 충돌체가 사용할 물리 재질을 설정하거나 가져옵니다. null이 전달될 경우 기본 재질을 사용합니다.
		/// </summary>
		property PhysicsMaterial^ Material
		{
			PhysicsMaterial^ get();
			void set( PhysicsMaterial^ value );
		}
	};
}
