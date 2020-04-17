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
	/// ��ü�� ī�޶� ���� ��� ������ ����� �����մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
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
		/// <see cref="Camera"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Camera();
		~Camera();
		!Camera();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ī�޶� �����ϴ� ȭ�� ���� ������ �����ϴ� ��ġ ��ǥ���� ���� �������� �����Ǵ� ���� ������ �����ɴϴ�.
		/// </summary>
		/// <param name="screenPoint"> ȭ�� ���� ��ġ ��ǥ�� �����մϴ�. </param>
		Ray ScreenPointToRay( System::Drawing::Point screenPoint );

		/// <summary>
		/// ī�޶��� ��Ⱦ�� �����ɴϴ�. 0�� �ڵ� �� ������ ��Ÿ���ϴ�.
		/// </summary>
		property float AspectRatio
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ī�޶��� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property Texture2D^ Skybox
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}
	};
}