#pragma once

namespace SC::Game
{
	ref class Animator;
	ref class SkinnedMeshRenderer;

	class SkinnedMeshRendererQueue
	{
	public:
		struct SkinnedPair
		{
			gcroot<Animator^> pAnimator;
			std::list<gcroot<SkinnedMeshRenderer^>> SkinnedMeshRenderers;
		};

		std::list<SkinnedPair> mSkinnedPair;

		gcroot<Animator^> mAnimator;
		std::list<gcroot<SkinnedMeshRenderer^>> mSkinnedMeshRenderers;

	public:
		SkinnedMeshRendererQueue();

		void Clear();
		void PushAnimator( Animator^ pAnimator );
		void AddRenderer( SkinnedMeshRenderer^ pRenderer );
	};
}