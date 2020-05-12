#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// ��û�� ���÷��� ������ ǥ���մϴ�.
	/// </summary>
	public value struct OutputQueryInfo
	{
	internal:
		System::String^ mDeviceName;
		System::Drawing::Rectangle mDesktopCoordinate;
		RotationMode mRotationMode;
		System::IntPtr mNativeHandle;

	public:
		/// <summary>
		/// ��ġ�� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ DeviceName
		{
			System::String^ get()
			{
				return mDeviceName;
			}
		}

		/// <summary>
		/// ��ġ�� ����ũž ������ �����ɴϴ�.
		/// </summary>
		property System::Drawing::Rectangle DesktopCoordinate
		{
			System::Drawing::Rectangle get()
			{
				return mDesktopCoordinate;
			}
		}

		/// <summary>
		/// ��ġ�� ��Ÿ���� ����ũž�� ȸ�� ������ �����ɴϴ�.
		/// </summary>
		property RotationMode Rotation
		{
			DXGI::RotationMode get()
			{
				return mRotationMode;
			}
		}

		/// <summary>
		/// ��ġ�� ����Ƽ�� �ڵ��� �����ɴϴ�.
		/// </summary>
		property System::IntPtr NativeHandle
		{
			System::IntPtr get()
			{
				return mNativeHandle;
			}
		}
	};
}