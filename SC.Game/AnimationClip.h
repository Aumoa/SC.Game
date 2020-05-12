#pragma once

namespace SC::Game
{
	/// <summary>
	/// 단일 애니메이션 장면을 표현합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="AnimationClip"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산 이름을 전달합니다. </param>
		AnimationClip( System::String^ xName );

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대에 관련된 키프레임 목록을 제거합니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		void RemoveKeyframes( System::String^ boneName );

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대에 관련된 키프레임 목록을 추가합니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		/// <param name="keyframes"> 키프레임 목록을 전달합니다. </param>
		void AddKeyframes( System::String^ boneName, Keyframes keyframes );

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대 이름을 변경합니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		/// <param name="rename"> 변경할 새로운 뼈대 이름을 전달합니다. </param>
		/// <param name="scaleFactor"> 변경한 후 값의 비례를 전달합니다. </param>
		/// <remarks> 일반적으로, 이 작업은 다른 형식으로 생성된 애니메이션 클립을 이 애니메이션 모델에 적용합니다. </remarks>
		void RenameKeyframes( System::String^ boneName, System::String^ rename, float scaleFactor );

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대 이름을 변경합니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		/// <param name="rename"> 변경할 새로운 뼈대 이름을 전달합니다. </param>
		/// <remarks> 일반적으로, 이 작업은 다른 형식으로 생성된 애니메이션 클립을 이 애니메이션 모델에 적용합니다. </remarks>
		void RenameKeyframes( System::String^ boneName, System::String^ rename )
		{
			RenameKeyframes( boneName, rename, 1.0f );
		}

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대에 관련된 키프레임 목록을 가져옵니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		Keyframes GetKeyframes( System::String^ boneName );

		/// <summary>
		/// 뼈대 키프레임 목록에서 뼈대에 관련된 키프레임 목록이 있는지 검사합니다.
		/// </summary>
		/// <param name="boneName"> 뼈대 이름을 전달합니다. </param>
		bool HasKeyframes( System::String^ boneName );

		/// <summary>
		/// 애니메이션의 마지막 키프레임 시간 위치를 가져옵니다.
		/// </summary>
		property float Duration
		{
			float get();
		}

		/// <summary>
		/// 애니메이션이 반복하는지 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property bool IsLoop
		{
			bool get();
			void set( bool value );
		}
	};
}