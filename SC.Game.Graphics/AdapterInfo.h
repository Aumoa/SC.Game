#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// 어댑터 정보를 표현합니다.
	/// </summary>
	public value struct AdapterInfo
	{
	internal:
		System::String^ mDescription;
		int mVendorId;
		int mDeviceId;
		long long mDedicatedVideoMemory;
		long long mDedicatedSystemMemory;
		long long mSharedSystemMemory;
		bool mSoftware;

	public:
		/// <summary>
		/// 어댑터 설명 텍스트를 가져옵니다.
		/// </summary>
		property System::String^ Description
		{
			System::String^ get()
			{
				return mDescription;
			}
		}

		/// <summary>
		/// 디바이스의 제공자 ID를 가져옵니다.
		/// </summary>
		property int VendorID
		{
			int get()
			{
				return mVendorId;
			}
		}

		/// <summary>
		/// 디바이스의 ID를 가져옵니다.
		/// </summary>
		property int DeviceID
		{
			int get()
			{
				return mDeviceId;
			}
		}

		/// <summary>
		/// 비디오 전용 메모리의 용량을 바이트 단위로 가져옵니다.
		/// </summary>
		property long long DedicatedVideoMemory
		{
			long long get()
			{
				return mDedicatedVideoMemory;
			}
		}

		/// <summary>
		/// 시스템 전용 메모리의 용량을 바이트 단위로 가져옵니다.
		/// </summary>
		property long long DedicatedSystemMemory
		{
			long long get()
			{
				return mDedicatedSystemMemory;
			}
		}

		/// <summary>
		/// 공유된 시스템 메모리의 용량을 바이트 단위로 가져옵니다.
		/// </summary>
		property long long SharedSystemMemory
		{
			long long get()
			{
				return mSharedSystemMemory;
			}
		}

		/// <summary>
		/// 어댑터가 소프트웨어 구현을 사용하는지 여부를 가져옵니다.
		/// </summary>
		property bool IsSoftware
		{
			bool get()
			{
				return mSoftware;
			}
		}
	};
}