#pragma once

namespace SC::Game
{
	/// <summary>
	/// ����� ���� ������Ʈ�� ���� ����� �����ϵ��� �մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Rigidbody sealed : public Component
	{
	internal:
		physx::PxRigidDynamic* mRigidbody = nullptr;

	public:
		/// <summary>
		/// <see cref="Rigidbody"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Rigidbody();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ������ٵ� ���� ���մϴ�.
		/// </summary>
		/// <param name="force"> ���� �����մϴ�. </param>
		void AddForce( System::Numerics::Vector3 force );

		/// <summary>
		/// ������ٵ� �̵��մϴ�.
		/// </summary>
		/// <param name="position"> �̵��� ��ġ�� �����մϴ�. </param>
		void MovePosition( System::Numerics::Vector3 position );

		/// <summary>
		/// ������ٵ��� ���¸� Ȱ��ȭ��ŵ�ϴ�.
		/// </summary>
		void WakeUp();
		
		/// <summary>
		/// ������ٵ��� ���¸� ��Ȱ��ȭ��ŵ�ϴ�.
		/// </summary>
		void Sleep();

		/// <summary>
		/// ������ٵ��� ��ġ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ������ٵ��� ȸ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// ���� ȿ���� �ش� ������ٵ� ������ �� �� �ִ��� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsKinematic
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// ������ٵ��� ���� ���� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property RigidbodyConstraints Constraints
		{
			RigidbodyConstraints get();
			void set( RigidbodyConstraints value );
		}

		/// <summary>
		/// ������ٵ��� ���� �ӵ��� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Velocity
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ������ٵ��� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Mass
		{
			float get();
			void set( float value );
		}
	};
}