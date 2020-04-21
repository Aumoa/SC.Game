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
	/// 개체에 조명 형식을 추가합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="Light"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Light();
		~Light();
		!Light();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 조명의 색을 설정하거나 가져옵니다.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// 조명의 주변광 값을 설정하거나 가져옵니다.
		/// </summary>
		property float Ambient
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 조명의 분산광 값을 설정하거나 가져옵니다.
		/// </summary>
		property float Diffuse
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 조명의 반영광 값을 설정하거나 가져옵니다.
		/// </summary>
		property float Specular
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 조명이 그림자를 생성하는지 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		property bool IsShadowCast
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// 조명이 그림자를 생성할 경우, 그림자 맵의 해상도를 설정하거나 가져옵니다.
		/// </summary>
		property System::Drawing::Size ShadowResolution
		{
			System::Drawing::Size get();
			void set( System::Drawing::Size value );
		}

		/// <summary>
		/// 조명이 그림자를 생성할 경우, 그림자 맵이 개체를 포함하는 크기를 설정하거나 가져옵니다.
		/// </summary>
		property float Width
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 조명이 그림자를 생성할 경우, 그림자 맵이 개체를 포함하는 크기를 설정하거나 가져옵니다.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}
	};
}