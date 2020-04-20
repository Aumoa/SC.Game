#pragma once

namespace SC::Game
{
	/// <summary>
	/// 광선 추적 함수의 결과를 표현합니다.
	/// </summary>
	public value struct RaycastHit
	{
		/// <summary>
		/// 충돌체 개체와 충돌했는지 여부를 나타냅니다.
		/// </summary>
		bool Hit;

		/// <summary>
		/// 충돌 지점까지의 거리를 나타냅니다.
		/// </summary>
		float Distance;

		/// <summary>
		/// 충돌한 표면의 법선을 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 Normal;
		
		/// <summary>
		/// 충돌한 지점의 세계 좌표를 나타냅니다.
		/// </summary>
		System::Numerics::Vector3 Point;

		/// <summary>
		/// 충돌한 콜라이더 개체를 가져옵니다.
		/// </summary>
		Collider^ Collider;
	};
}