#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ִϸ��̼� ���¸� ��Ÿ���ϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class AnimationState sealed : public Asset
	{
		AnimationClip^ mClip;

	public:
		/// <summary>
		/// <see cref="AnimationState"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ��� �ĺ��� �̸��� �����մϴ�. </param>
		AnimationState( System::String^ xName );

		/// <summary>
		/// ��� ��� �ִϸ��̼� Ŭ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property AnimationClip^ Clip
		{
			AnimationClip^ get();
			void set( AnimationClip^ value );
		}
	};
}
