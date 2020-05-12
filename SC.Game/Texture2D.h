#pragma once

namespace SC::Game
{
	/// <summary>
	/// 2���� �ؽ�ó �����͸� ǥ���մϴ�.
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
		/// <see cref="Texture2D"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ� �̸��� �����մϴ�. </param>
		/// <param name="filepath"> �̹��� ���� ��θ� �����մϴ�. </param>
		/// <param name="format"> �̹��� ������ �����մϴ�. </param>
		Texture2D( System::String^ xName, System::String^ filepath, TextureFormat format );

		/// <summary>
		/// <see cref="Texture2D"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ� �̸��� �����մϴ�. </param>
		/// <param name="textureData"> �ؽ�ó �����͸� �����մϴ�. </param>
		/// <param name="sizeInBytes"> �ؽ�ó �������� ũ�⸦ �����մϴ�. </param>
		/// <param name="format"> �̹��� ������ �����մϴ�. </param>
		Texture2D( System::String^ xName, cli::array<System::Byte>^ textureData, System::UInt32 sizeInBytes, TextureFormat format );

		/// <summary>
		/// (<see cref="Asset"/> Ŭ�������� ��� ��.) ��ü�� ������ ������ �ؽ�Ʈ �������� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// �ؽ�ó ��ü�� �ȼ� ���̸� �����ɴϴ�.
		/// </summary>
		property System::UInt32 Width
		{
			System::UInt32 get();
		}

		/// <summary>
		/// �ؽ�ó ��ü�� �ȼ� ���̸� �����ɴϴ�.
		/// </summary>
		property System::UInt32 Height
		{
			System::UInt32 get();
		}
	};
}