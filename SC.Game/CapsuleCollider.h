#pragma once

namespace SC::Game
{
	/// <summary>
	/// 캡슐 형태의 기본 충돌체를 나타냅니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class CapsuleCollider sealed : public Collider
	{
	internal:
		float mHalfHeight = 1.0f;
		float mRadius = 1.0f;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="BoxCollider"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		CapsuleCollider();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 캡슐의 X축 높이를 나타내는 값을 설정하거나 가져옵니다. 개체의 로컬 좌표로 측정됩니다.
		/// </summary>
		/// <remarks> Y축을 높이로 사용하는 좌표계에선 <see cref="Collider::Rotation"/> 속성을 사용하여 회전시켜 사용합니다. </remarks>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 캡슐의 반지름을 나타내는 값을 설정하거나 가져옵니다. 개체의 로컬 좌표로 측정됩니다.
		/// </summary>
		/// <remarks> 캡슐의 반지름의 0.25배만큼 캡슐의 높이가 커집니다. </remarks>
		property float Radius
		{
			float get();
			void set( float value );
		}
	};
}