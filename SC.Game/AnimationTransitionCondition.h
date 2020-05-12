#pragma once

namespace SC::Game
{
	public delegate bool AnimVarConditionDelegate( System::Object^ value );

	/// <summary>
	/// 애니메이션 상태 전환을 위한 매개변수 및 조건을 표현합니다.
	/// </summary>
	public value struct AnimationTransitionCondition
	{
		/// <summary>
		/// 전환할 애니메이션 상태 이름을 설정합니다.
		/// </summary>
		System::String^ To;

		/// <summary>
		/// 조건 매개변수 이름을 설정합니다.
		/// </summary>
		System::String^ VarName;

		/// <summary>
		/// 조건을 테스트할 함수를 설정합니다.
		/// </summary>
		AnimVarConditionDelegate^ Condition;

		/// <summary>
		/// 애니메이션 재생 시간이 종료될 경우 전환을 가집니다.
		/// </summary>
		bool HasExitTime;

		/// <summary>
		/// 이 전환이 진행되는 시간을 설정합니다.
		/// </summary>
		float BlendTime;

		/// <summary>
		/// <see cref="AnimationTransitionCondition"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="to"> 전환할 애니메이션 상태 이름을 전달합니다. </param>
		/// <param name="varName"> 조건 매개변수 이름을 전달합니다. </param>
		/// <param name="blendTime"> 이 전환이 진행되는 시간을 전달합니다. </param>
		/// <param name="condition"> 조건을 테스트할 함수를 전달합니다. </param>
		AnimationTransitionCondition( System::String^ to, System::String^ varName, float blendTime, AnimVarConditionDelegate^ condition )
		{
			this->To = to;
			this->VarName = varName;
			this->Condition = condition;
			this->HasExitTime = false;
			this->BlendTime = blendTime;
		}
	};
}