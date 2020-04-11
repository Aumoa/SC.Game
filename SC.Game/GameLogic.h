#pragma once

namespace SC::Game
{
	ref class Scene;

	class GameLogic abstract
	{
	public:
		static gcroot<Scene^> mCurrentScene;
		static gcroot<Scene^> mRemovedScenes[2];

		static CDeviceContext mDeviceContext;

		static GeometryBuffer mGeometryBuffer;
		static HDRBuffer mHDRBuffer;

		static D3D12_RECT mScissorRect;
		static D3D12_VIEWPORT mViewport;

	public:
		static void Initialize();

		static void Update();
		static void Render();

	private:
		static void OnDisposing();
		static void OnResizing( int width, int height );

		static void GeometryWriting();
		static void Present();
	};
}