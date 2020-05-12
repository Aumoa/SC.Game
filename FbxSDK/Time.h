#pragma once

namespace FbxSDK
{
	/// <summary>
	/// �ִϸ��̼� �ð��� ǥ���մϴ�.
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
		/// �ð��� ��Ÿ���� ������ ���� �����ɴϴ�.
		/// </summary>
		/// <param name="timeMode"> ������ ���� �ǹ��ϴ� �ð� ������ �����մϴ�. </param>
		System::Int64 GetFrameCount( TimeMode timeMode )
		{
			return mFbxTime->GetFrameCount( ( FbxTime::EMode )timeMode );
		}

		/// <summary>
		/// �ð��� ������ ���� ��Ÿ���� ������ �����մϴ�.
		/// </summary>
		/// <param name="frameCount"> ������ ���� �����մϴ�. </param>
		/// <param name="timeMode"> ������ ���� �ǹ��ϴ� �ð� ������ �����մϴ�. </param>
		void SetFrame( System::Int64 frameCount, TimeMode timeMode )
		{
			mFbxTime->SetFrame( frameCount, ( FbxTime::EMode )timeMode );
		}
	};
}