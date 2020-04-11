#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 개체에 특정한 행동을 추가하는 확장 구성 요소에 대한 기본 함수를 제공합니다.
	/// </summary>
	public ref class Behaviour abstract : public Component
	{
	internal:
		bool mIsEnabled = true;
		bool mIsFirst = true;

		void InternalUpdate();

	protected:
		/// <summary>
		/// <see cref="Behaviour"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Behaviour();

	public:
		/// <summary>
		/// 컴포넌트가 개체와 연결될 때 호출됩니다.
		/// </summary>
		virtual void Awake();

		/// <summary>
		/// 컴포넌트가 게임 논리에 처음으로 관여할 때 호출됩니다.
		/// </summary>
		/// <remarks> 일반적으로, 이 함수는 해당 컴포넌트의 첫 번째 Update 함수 호출 전에 실행됩니다. </remarks>
		virtual void Start();

		/// <summary>
		/// 행동 컴포넌트가 활성화 상태일 때 매 프레임 호출됩니다.
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 행동 컴포넌트가 활성화 상태일 때 매 고정 프레임 주기로 호출됩니다.
		/// </summary>
		/// <remarks> 고정 프레임 주기를 변경하려면 <see cref="AppConfiguration"/> 클래스를 참조하십시오. </remarks>
		virtual void FixedUpdate();

		/// <summary>
		/// 행동 컴포넌트가 활성화 상태일 때 매 프레임 장면의 모든 개체의 Update가 완료된 후 호출됩니다.
		/// </summary>
		virtual void LateUpdate();
	};
}