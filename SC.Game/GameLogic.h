#pragma once

namespace SC::Game
{
	ref class Scene;

	class GameLogic abstract
	{
	public:
		static CDeviceContext mDeviceContext;
		static gcroot<Scene^> mCurrentScene;
		static gcroot<Scene^> mRemovedScenes[2];

	public:
		static void Initialize();

		static void Update();
		static void Render();

	private:
		static void OnDisposing();

		static void Present();
	};
}