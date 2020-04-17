#pragma once

namespace SC::Game
{
	ref class Scene;
	ref class Mesh;
	ref class Light;

	class GameLogic abstract
	{
	public:
		static gcroot<Scene^> mCurrentScene;
		static gcroot<Scene^> mRemovedScenes[2];

		static CDeviceContext mDeviceContext;
		static CDeviceContext mDeviceContextGeometryWriting;
		static CDeviceContext mDeviceContextShadowCast[8];
		static CDeviceContext mDeviceContextHDR;
		static CDeviceContext mDeviceContextHDRCompute;

		static GeometryBuffer mGeometryBuffer;
		static HDRBuffer mHDRBuffer;
		static HDRComputedBuffer mHDRComputedBuffer;

		static D3D12_RECT mScissorRect;
		static D3D12_VIEWPORT mViewport;

		static gcroot<Mesh^> mMesh;

	public:
		static void Initialize();

		static void Update();
		static void Render();

	private:
		static void OnDisposing();
		static void OnResizing( int width, int height );

		static void GeometryWriting();
		static cli::array<System::Threading::Tasks::Task^>^ ShadowCast();
		static void HDRRender();
		static void HDRCompute();
		static void Present();

	public:
		static void ShadowRender( Light^ light, int threadIdx );
	};
}