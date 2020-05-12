#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 애니메이션 시간을 표현합니다.
	/// </summary>
	public ref class Time
	{
	internal:
		FbxTime* mFbxTime = nullptr;

	internal:
		Time()
		{
			mFbxTime = new FbxTime();
		}

	public:
		~Time()
		{
			this->!Time();
		}

		!Time()
		{
			if ( mFbxTime )
			{
				delete mFbxTime;
				mFbxTime = nullptr;
			}
		}

		/// <summary>
		/// 시간이 나타내는 프레임 수를 가져옵니다.
		/// </summary>
		/// <param name="timeMode"> 프레임 수가 의미하는 시간 형식을 전달합니다. </param>
		System::Int64 GetFrameCount( TimeMode timeMode )
		{
			return mFbxTime->GetFrameCount( ( FbxTime::EMode )timeMode );
		}

		/// <summary>
		/// 시간을 프레임 수가 나타내는 값으로 설정합니다.
		/// </summary>
		/// <param name="frameCount"> 프레임 수를 전달합니다. </param>
		/// <param name="timeMode"> 프레임 수가 의미하는 시간 형식을 전달합니다. </param>
		void SetFrame( System::Int64 frameCount, TimeMode timeMode )
		{
			mFbxTime->SetFrame( frameCount, ( FbxTime::EMode )timeMode );
		}
	};
}