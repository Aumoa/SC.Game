#pragma once

namespace SC::Game
{
	/// <summary>
	/// 박스 형태의 기본 충돌체를 나타냅니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class BoxCollider sealed : public Collider
	{
	internal:
		System::Numerics::Vector3 mHalfExtents;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="BoxCollider"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		BoxCollider();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 박스의 확장 크기를 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 HalfExtents
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}
	};
}