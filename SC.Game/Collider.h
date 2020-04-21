#pragma once

namespace SC::Game
{
	/// <summary>
	/// ��� �浹ü(Collider)�� �⺻ Ŭ������ ��Ÿ���ϴ�.
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
		/// �浹ü ����� �߽��� ��Ÿ���� ���� �����ϰų� �����ɴϴ�. ��ü�� ���� ��ǥ�� �����˴ϴ�.
		/// </summary>
		property System::Numerics::Vector3 Center
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// �浹ü ����� ȸ���� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// �� �浹ü�� �̺�Ʈ�� �߻���Ű�� Ʈ���� �浹ü���� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsTrigger
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// �浹ü�� ����� ���� ������ �����ϰų� �����ɴϴ�. null�� ���޵� ��� �⺻ ������ ����մϴ�.
		/// </summary>
		property PhysicsMaterial^ Material
		{
			PhysicsMaterial^ get();
			void set( PhysicsMaterial^ value );
		}
	};
}
