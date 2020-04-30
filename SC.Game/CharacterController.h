#pragma once

namespace SC::Game
{
	/// <summary>
	/// 물리 영향 하의 게임 캐릭터를 제어할 수 있는 수단을 제공합니다.
	/// </summary>
	public ref class CharacterController : public Rigidbody
	{
	internal:
		physx::PxController* mController = nullptr;

		float mRadius = 1.0f;
		float mHeight = 0.5f;
		float mSlopeLimit = 0.707f;
		float mDensity = 1.0f;
		float mStepOffset = 0.0f;

	public:
		/// <summary>
		/// <see cref="CharacterController"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		CharacterController();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 컨트롤러 개체의 위치를 이동합니다.
		/// </summary>
		/// <param name="value"> 위치의 상대값을 전달합니다. </param>
		void MovePosition( System::Numerics::Vector3 value );

		/// <summary>
		/// 캐릭터의 반경을 설정하거나 가져옵니다.
		/// </summary>
		property float Radius
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 캐릭터의 높이를 설정하거나 가져옵니다.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 캐릭터가 등반할 수 있는 벽의 최대 각도를 설정하거나 가져옵니다.
		/// </summary>
		property float SlopeLimit
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 캐릭터 컨트롤러 콜라이더 개체의 질량을 설정하거나 가져옵니다.
		/// </summary>
		property float Density
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 캐릭터가 등반할 수 있는 최대 높이를 설정하거나 가져옵니다.
		/// </summary>
		property float StepOffset
		{
			float get();
			void set( float value );
		}
	};
}