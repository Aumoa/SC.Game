#pragma once

namespace SC::Game
{
	/// <summary>
	/// 3차원 광선 정보를 표현합니다.
	/// </summary>
	public value struct Ray
	{
		/// <summary>
		/// 광선의 시작 위치를 설정합니다.
		/// </summary>
		System::Numerics::Vector3 Origin;

		/// <summary>
		/// 광선의 정규화된 진행 방향 벡터를 설정합니다.
		/// </summary>
		System::Numerics::Vector3 Direction;

		/// <summary>
		/// 광선의 최대 깊이를 설정합니다. 0일 경우 제한 없음을 나타냅니다.
		/// </summary>
		float MaxDepth;

	public:
		/// <summary>
		/// <see cref="Ray"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="origin"> 광선의 시작 위치를 전달합니다. </param>
		/// <param name="direction"> 광선의 정규화된 진행 방향 벡터를 전달합니다. </param>
		Ray( System::Numerics::Vector3 origin, System::Numerics::Vector3 direction );

		/// <summary>
		/// <see cref="Ray"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="origin"> 광선의 시작 위치를 전달합니다. </param>
		/// <param name="direction"> 광선의 정규화된 진행 방향 벡터를 전달합니다. </param>
		/// <param name="maxDepth"> 광선의 최대 깊이를 전달합니다. 0일 경우 제한 없음을 나타냅니다. </param>
		Ray( System::Numerics::Vector3 origin, System::Numerics::Vector3 direction, float maxDepth );

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 광선의 정보를 서식화된 텍스트로 가져옵니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// 광선 진행 방향으로 거리만큼 이동했을 때의 위치를 가져옵니다.
		/// </summary>
		/// <param name="distance"> 거리를 전달합니다. </param>
		System::Numerics::Vector3 GetPoint( float distance );
	};
}