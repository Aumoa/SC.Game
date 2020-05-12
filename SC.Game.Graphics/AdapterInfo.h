#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// ����� ������ ǥ���մϴ�.
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
		/// ����� ���� �ؽ�Ʈ�� �����ɴϴ�.
		/// </summary>
		property System::String^ Description
		{
			System::String^ get()
			{
				return mDescription;
			}
		}

		/// <summary>
		/// ����̽��� ������ ID�� �����ɴϴ�.
		/// </summary>
		property int VendorID
		{
			int get()
			{
				return mVendorId;
			}
		}

		/// <summary>
		/// ����̽��� ID�� �����ɴϴ�.
		/// </summary>
		property int DeviceID
		{
			int get()
			{
				return mDeviceId;
			}
		}

		/// <summary>
		/// ���� ���� �޸��� �뷮�� ����Ʈ ������ �����ɴϴ�.
		/// </summary>
		property long long DedicatedVideoMemory
		{
			long long get()
			{
				return mDedicatedVideoMemory;
			}
		}

		/// <summary>
		/// �ý��� ���� �޸��� �뷮�� ����Ʈ ������ �����ɴϴ�.
		/// </summary>
		property long long DedicatedSystemMemory
		{
			long long get()
			{
				return mDedicatedSystemMemory;
			}
		}

		/// <summary>
		/// ������ �ý��� �޸��� �뷮�� ����Ʈ ������ �����ɴϴ�.
		/// </summary>
		property long long SharedSystemMemory
		{
			long long get()
			{
				return mSharedSystemMemory;
			}
		}

		/// <summary>
		/// ����Ͱ� ����Ʈ���� ������ ����ϴ��� ���θ� �����ɴϴ�.
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