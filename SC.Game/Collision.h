#pragma once

namespace SC::Game
{
	value struct ContactPoint;
	ref class GameObject;

	/// <summary>
	/// 충돌 정보를 나타냅니다.
	/// </summary>
	public value struct Collision
	{
		/// <summary>
		/// 물리 엔진에 의해 생성되는 충돌점 목록을 나타냅니다.
		/// </summary>
		System::Collections::Generic::IList<ContactPoint>^ Contacts;

		/// <summary>
		/// 충돌이 감지된 충돌체의 게임 개체를 나타냅니다.
		/// </summary>
		GameObject^ Object;

		/// <summary>
		/// 충돌을 해결하는 데 적용되는 총 힘을 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 Impulse;

		/// <summary>
		/// 충돌하는 두 오브젝트의 상대적 선형 속도를 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 RelativeVelocity;

		/// <summary>
		/// 충돌이 감지된 대상 충돌체의 게임 개체를 나타냅니다.
		/// </summary>
		GameObject^ Target;
	};
}