#pragma once

namespace SC::Game
{
	/// <summary>
	/// 충돌이 발생한 충돌점을 나타냅니다.
	/// </summary>
	public value struct ContactPoint
	{
		/// <summary>
		/// 충돌 지점의 노멀 값을 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// 충돌을 생성한 첫 번째 충돌체를 나타냅니다.
		/// </summary>
		Collider^ ThisCollider;

		/// <summary>
		/// 충돌을 생성한 두 번째 충돌체를 나타냅니다.
		/// </summary>
		Collider^ OtherCollider;

		/// <summary>
		/// 충돌 위치를 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 Point;
	};
}