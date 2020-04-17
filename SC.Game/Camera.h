#pragma once

namespace SC::Game
{
	struct Camera_Constants
	{
		XMFLOAT4X4 ViewProj;
		XMFLOAT4X4 ViewInv;
		XMFLOAT4X4 ProjInv;
		XMFLOAT3 Pos;

		void Initialize();
	};

	ref class Texture2D;

	/// <summary>
	/// 개체에 카메라 구성 요소 렌더링 기능을 제공합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class Camera sealed : public Component
	{
	internal:
		Heap* mConstantBuffer = nullptr;
		Camera_Constants* mFrameResource = nullptr;

		float mAspectRatio = 0.0f;
		float mMaxDepth = 1000.0f;

		cli::array<System::Numerics::Plane>^ mPlanes;
		bool mUpdated = true;

		Texture2D^ mSkyboxTexture;

	internal:
		void Update();

	public:
		/// <summary>
		/// <see cref="Camera"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Camera();
		~Camera();
		!Camera();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 카메라가 제공하는 화면 공간 영역에 존재하는 위치 좌표에서 세계 공간으로 투영되는 광선 정보를 가져옵니다.
		/// </summary>
		/// <param name="screenPoint"> 화면 공간 위치 좌표를 전달합니다. </param>
		Ray ScreenPointToRay( System::Drawing::Point screenPoint );

		/// <summary>
		/// 카메라의 종횡비를 가져옵니다. 0은 자동 값 설정을 나타냅니다.
		/// </summary>
		property float AspectRatio
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 카메라의 전경을 설정하거나 가져옵니다.
		/// </summary>
		property Texture2D^ Skybox
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}
	};
}