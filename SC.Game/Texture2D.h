#pragma once

namespace SC::Game
{
	/// <summary>
	/// 2차원 텍스처 데이터를 표현합니다.
	/// </summary>
	public ref class Texture2D : public Asset
	{
	internal:
		ID3D12Resource* mTexture2D = nullptr;
		CShaderResourceView* mShaderResourceView = nullptr;

		System::UInt32 mWidth = 0;
		System::UInt32 mHeight = 0;

		System::String^ mFilename;

	private:
		void InitializeFrom( IWICBitmapDecoder* pDecoder, TextureFormat format );

	public:
		~Texture2D();
		!Texture2D();

		/// <summary>
		/// <see cref="Texture2D"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산 이름을 제공합니다. </param>
		/// <param name="filepath"> 이미지 파일 경로를 전달합니다. </param>
		/// <param name="format"> 이미지 형식을 전달합니다. </param>
		Texture2D( System::String^ xName, System::String^ filepath, TextureFormat format );

		/// <summary>
		/// <see cref="Texture2D"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산 이름을 제공합니다. </param>
		/// <param name="textureData"> 텍스처 데이터를 전달합니다. </param>
		/// <param name="sizeInBytes"> 텍스처 데이터의 크기를 전달합니다. </param>
		/// <param name="format"> 이미지 형식을 전달합니다. </param>
		Texture2D( System::String^ xName, cli::array<System::Byte>^ textureData, System::UInt32 sizeInBytes, TextureFormat format );

		/// <summary>
		/// (<see cref="Asset"/> 클래스에서 상속 됨.) 개체의 간단한 정보를 텍스트 형식으로 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// 텍스처 개체의 픽셀 넓이를 가져옵니다.
		/// </summary>
		property System::UInt32 Width
		{
			System::UInt32 get();
		}

		/// <summary>
		/// 텍스처 개체의 픽셀 높이를 가져옵니다.
		/// </summary>
		property System::UInt32 Height
		{
			System::UInt32 get();
		}
	};
}