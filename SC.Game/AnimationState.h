#pragma once

namespace SC::Game
{
	/// <summary>
	/// 애니메이션 상태를 나타냅니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class AnimationState sealed : public Asset
	{
		AnimationClip^ mClip;

	public:
		/// <summary>
		/// <see cref="AnimationState"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산의 식별자 이름을 전달합니다. </param>
		AnimationState( System::String^ xName );

		/// <summary>
		/// 재생 대상 애니메이션 클립을 설정하거나 가져옵니다.
		/// </summary>
		property AnimationClip^ Clip
		{
			AnimationClip^ get();
			void set( AnimationClip^ value );
		}
	};
}
