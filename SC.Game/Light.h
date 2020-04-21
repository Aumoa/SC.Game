#pragma once

namespace SC::Game
{
	struct Light_Constants
	{
		int Type;
		XMFLOAT3 Color;
		float Ambient;
		float Diffuse;
		float Specular;
		int ShadowCast;
		XMFLOAT4X4 ViewProj;
		XMFLOAT3 Direction;
		float Range;
		XMFLOAT4 Position;
	};

	/// <summary>
	/// ��ü�� ���� ������ �߰��մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Light : public Component
	{
	internal:
		System::Drawing::Size mShadowResolution;

		Heap* mConstantBuffer = nullptr;
		Light_Constants* mFrameResource = nullptr;
		bool mFrameUpdated = false;

		ID3D12Resource* mShadowMap = nullptr;
		ID3D12DescriptorHeap* mDSVHeap = nullptr;
		CShaderResourceView* mShaderResourceView = nullptr;

		float mWidth = 30.0f;
		float mHeight = 30.0f;

	private:
		void InitializeDepthBuffer();

	internal:
		void UpdateBuffer();
		void BeginDraw( CDeviceContext& deviceContext );
		void EndDraw( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// <see cref="Light"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Light();
		~Light();
		!Light();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ������ ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// ������ �ֺ��� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Ambient
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ �л걤 ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Diffuse
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ �ݿ��� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Specular
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ �׸��ڸ� �����ϴ��� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsShadowCast
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// ������ �׸��ڸ� ������ ���, �׸��� ���� �ػ󵵸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Size ShadowResolution
		{
			System::Drawing::Size get();
			void set( System::Drawing::Size value );
		}

		/// <summary>
		/// ������ �׸��ڸ� ������ ���, �׸��� ���� ��ü�� �����ϴ� ũ�⸦ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Width
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ �׸��ڸ� ������ ���, �׸��� ���� ��ü�� �����ϴ� ũ�⸦ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}
	};
}