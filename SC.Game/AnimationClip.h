#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �ִϸ��̼� ����� ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class AnimationClip sealed : public Asset
	{
	internal:
		System::Collections::Generic::IDictionary<System::String^, Keyframes>^ mKeyframes;
		float mDuration = 0.0f;
		bool mIsLoop = false;
		bool mIsEmpty = true;

	private:
		void ComputeDur();

	internal:
		System::Collections::Generic::IDictionary<System::String^, KeyframePair>^ MakeInterpolateMap();
		void Interpolate( float timePos, System::Collections::Generic::IDictionary<System::String^, KeyframePair>^ interpolated );

	public:
		/// <summary>
		/// <see cref="AnimationClip"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ� �̸��� �����մϴ�. </param>
		AnimationClip( System::String^ xName );

		/// <summary>
		/// ���� Ű������ ��Ͽ��� ���뿡 ���õ� Ű������ ����� �����մϴ�.
		/// </summary>
		/// <param name="boneName"> ���� �̸��� �����մϴ�. </param>
		void RemoveKeyframes( System::String^ boneName );

		/// <summary>
		/// ���� Ű������ ��Ͽ��� ���뿡 ���õ� Ű������ ����� �߰��մϴ�.
		/// </summary>
		/// <param name="boneName"> ���� �̸��� �����մϴ�. </param>
		/// <param name="keyframes"> Ű������ ����� �����մϴ�. </param>
		void AddKeyframes( System::String^ boneName, Keyframes keyframes );

		/// <summary>
		/// ���� Ű������ ��Ͽ��� ���뿡 ���õ� Ű������ ����� �����ɴϴ�.
		/// </summary>
		/// <param name="boneName"> ���� �̸��� �����մϴ�. </param>
		Keyframes GetKeyframes( System::String^ boneName );

		/// <summary>
		/// �ִϸ��̼��� ������ Ű������ �ð� ��ġ�� �����ɴϴ�.
		/// </summary>
		property float Duration
		{
			float get();
		}

		/// <summary>
		/// �ִϸ��̼��� �ݺ��ϴ��� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsLoop
		{
			bool get();
			void set( bool value );
		}
	};
}