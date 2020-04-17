#pragma once

namespace SC::Game
{
	/// <summary>
	/// 연결된 게임 오브젝트가 물리 제어로 동작하도록 합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class Rigidbody sealed : public Component
	{
	internal:
		physx::PxRigidDynamic* mRigidbody = nullptr;

	public:
		/// <summary>
		/// <see cref="Rigidbody"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Rigidbody();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 리지드바디에 힘을 가합니다.
		/// </summary>
		/// <param name="force"> 힘을 전달합니다. </param>
		void AddForce( System::Numerics::Vector3 force );

		/// <summary>
		/// 리지드바디를 이동합니다.
		/// </summary>
		/// <param name="position"> 이동할 위치를 전달합니다. </param>
		void MovePosition( System::Numerics::Vector3 position );

		/// <summary>
		/// 리지드바디의 상태를 활성화시킵니다.
		/// </summary>
		void WakeUp();
		
		/// <summary>
		/// 리지드바디의 상태를 비활성화시킵니다.
		/// </summary>
		void Sleep();

		/// <summary>
		/// 리지드바디의 위치를 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 리지드바디의 회전을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// 물리 효과가 해당 리지드바디에 영향을 줄 수 있는지 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property bool IsKinematic
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// 리지드바디의 강제 제약 사항을 설정하거나 가져옵니다.
		/// </summary>
		property RigidbodyConstraints Constraints
		{
			RigidbodyConstraints get();
			void set( RigidbodyConstraints value );
		}

		/// <summary>
		/// 리지드바디의 선형 속도를 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Velocity
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 리지드바디의 질량을 설정하거나 가져옵니다.
		/// </summary>
		property float Mass
		{
			float get();
			void set( float value );
		}
	};
}