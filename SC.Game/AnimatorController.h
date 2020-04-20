#pragma once

namespace SC::Game
{
	/// <summary>
	/// 애니메이션 상태를 제어하는 애니메이션 상태 집합을 표현합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class AnimatorController sealed : public Asset
	{
	internal:
		System::Collections::Generic::IDictionary<System::String^, AnimationState^>^ mStates;
		System::Collections::Generic::IDictionary<System::String^, System::Object^>^ mParameters;
		System::Collections::Generic::IDictionary<System::String^, System::Collections::Generic::IList<AnimationTransitionCondition>^>^ mTransitionCondition;

		System::String^ mDefaultState;

		System::Collections::Generic::IDictionary<System::String^, System::Object^>^ MakeParameters();

	public:
		/// <summary>
		/// <see cref="AnimatorController"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산 이름을 전달합니다. </param>
		AnimatorController( System::String^ xName );

		/// <summary>
		/// 애니메이션 상태 개체를 추가합니다.
		/// </summary>
		/// <param name="state"> 상태 개체를 전달합니다. 개체의 <see cref="Asset::Name"/> 값이 이름으로 사용됩니다. </param>
		/// <param name="isDefault"> 개체를 기본 상태로 사용합니다. </param>
		void AddState( AnimationState^ state, bool isDefault );

		/// <summary>
		/// 애니메이션 상태 개체를 추가합니다.
		/// </summary>
		/// <param name="state"> 상태 개체를 전달합니다. 개체의 <see cref="Asset::Name"/> 값이 이름으로 사용됩니다. </param>
		void AddState( AnimationState^ state ) { AddState( state, false ); }

		/// <summary>
		/// 애니메이션 상태 개체를 추가합니다.
		/// </summary>
		/// <param name="stateNameOverride"> 덮어쓸 새로운 상태 개체 이름을 전달합니다. </param>
		/// <param name="state"> 상태 개체를 전달합니다. </param>
		/// <param name="isDefault"> 개체를 기본 상태로 사용합니다. </param>
		void AddState( System::String^ stateNameOverride, AnimationState^ state, bool isDefault );

		/// <summary>
		/// 애니메이션 상태 개체를 추가합니다.
		/// </summary>
		/// <param name="stateNameOverride"> 덮어쓸 새로운 상태 개체 이름을 전달합니다. </param>
		/// <param name="state"> 상태 개체를 전달합니다. </param>
		void AddState( System::String^ stateNameOverride, AnimationState^ state ) { AddState( stateNameOverride, state, false ); }

		/// <summary>
		/// 애니메이션 상태 개체를 제거합니다.
		/// </summary>
		/// <param name="stateName"> 상태 개체 이름을 전달합니다. </param>
		void RemoveState( System::String^ stateName );

		/// <summary>
		/// 애니메이션 상태 개체를 가져옵니다.
		/// </summary>
		/// <param name="stateName"> 상태 개체 이름을 전달합니다. </param>
		AnimationState^ GetState( System::String^ stateName );

		/// <summary>
		/// 새 애니메이션 매개변수를 추가합니다.
		/// </summary>
		/// <param name="stateName"> 상태 개체 이름을 전달합니다. </param>
		/// <param name="value"> 초기화 값이 포함된 매개변수 값을 전달합니다. </param>
		void AddVar( System::String^ stateName, System::Object^ value );

		/// <summary>
		/// 애니메이션 매개변수를 제거합니다.
		/// </summary>
		/// <param name="stateName"> 상태 개체 이름을 전달합니다. </param>
		void RemoveVar( System::String^ stateName );

		/// <summary>
		/// 애니메이션 매개변수 값을 가져옵니다.
		/// </summary>
		/// <param name="varName"> 매개변수 이름을 전달합니다. </param>
		System::Object^ GetVar( System::String^ varName );

		/// <summary>
		/// 애니메이션 전환 상태를 추가합니다.
		/// </summary>
		/// <param name="from"> 시작 애니메이션 상태 개체의 등록 이름을 전달합니다. </param>
		/// <param name="value"> 애니메이션 전환 조건 구조체를 전달합니다. </param>
		void AddTransition( System::String^ from, AnimationTransitionCondition value );

		/// <summary>
		/// 애니메이션 전환 상태를 제거합니다.
		/// </summary>
		/// <param name="from"> 시작 애니메이션 상태 개체의 등록 이름을 전달합니다. </param>
		/// <param name="value"> 애니메이션 전환 조건 구조체를 전달합니다. 값이 비어있을 경우 최상위 탐색 요소를 사용합니다. </param>
		void RemoveTransition( System::String^ from, AnimationTransitionCondition value );

		/// <summary>
		/// 애니메이션 전환 상태를 제거합니다.
		/// </summary>
		/// <param name="from"> 시작 애니메이션 상태 개체의 등록 이름을 전달합니다. </param>
		void RemoveTransition( System::String^ from ) { RemoveTransition( from, AnimationTransitionCondition() ); }

		/// <summary>
		/// 애니메이션 전환 상태를 가져옵니다.
		/// </summary>
		/// <param name="from"> 시작 애니메이션 상태 개체의 등록 이름을 전달합니다. </param>
		System::Collections::Generic::IList<AnimationTransitionCondition>^ GetTransition( System::String^ from );

		/// <summary>
		/// 기본 애니메이션 상태 개체 이름을 가져옵니다.
		/// </summary>
		property System::String^ DefaultState
		{
			System::String^ get();
		}
	};
}