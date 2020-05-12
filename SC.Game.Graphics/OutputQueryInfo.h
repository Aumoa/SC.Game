#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// 요청된 디스플레이 정보를 표현합니다.
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
		/// 장치의 이름을 가져옵니다.
		/// </summary>
		property System::String^ DeviceName
		{
			System::String^ get()
			{
				return mDeviceName;
			}
		}

		/// <summary>
		/// 장치의 데스크탑 영역을 가져옵니다.
		/// </summary>
		property System::Drawing::Rectangle DesktopCoordinate
		{
			System::Drawing::Rectangle get()
			{
				return mDesktopCoordinate;
			}
		}

		/// <summary>
		/// 장치가 나타내는 데스크탑의 회전 정보를 가져옵니다.
		/// </summary>
		property RotationMode Rotation
		{
			DXGI::RotationMode get()
			{
				return mRotationMode;
			}
		}

		/// <summary>
		/// 장치의 네이티브 핸들을 가져옵니다.
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