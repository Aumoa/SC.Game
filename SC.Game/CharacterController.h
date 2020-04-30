#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ���� ���� ���� ĳ���͸� ������ �� �ִ� ������ �����մϴ�.
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
		/// <see cref="CharacterController"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		CharacterController();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ��Ʈ�ѷ� ��ü�� ��ġ�� �̵��մϴ�.
		/// </summary>
		/// <param name="value"> ��ġ�� ��밪�� �����մϴ�. </param>
		void MovePosition( System::Numerics::Vector3 value );

		/// <summary>
		/// ĳ������ �ݰ��� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Radius
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ĳ������ ���̸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ĳ���Ͱ� ����� �� �ִ� ���� �ִ� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float SlopeLimit
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ĳ���� ��Ʈ�ѷ� �ݶ��̴� ��ü�� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Density
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ĳ���Ͱ� ����� �� �ִ� �ִ� ���̸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float StepOffset
		{
			float get();
			void set( float value );
		}
	};
}