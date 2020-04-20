using namespace SC;
using namespace SC::Game;

SkinnedMeshRendererQueue::SkinnedMeshRendererQueue()
{

}

void SkinnedMeshRendererQueue::Clear()
{
	mSkinnedPair.clear();

	mAnimator = nullptr;
	mSkinnedMeshRenderers.clear();
}

void SkinnedMeshRendererQueue::PushAnimator( Animator^ pAnimator )
{
	if ( mAnimator && mSkinnedMeshRenderers.size() )
	{
		SkinnedPair pair;

		pair.pAnimator = mAnimator;
		pair.SkinnedMeshRenderers = move( mSkinnedMeshRenderers );

		mSkinnedPair.push_back( pair );
	}

	mAnimator = pAnimator;
}

void SkinnedMeshRendererQueue::AddRenderer( SkinnedMeshRenderer^ pRenderer )
{
	if ( mAnimator )
	{
		mSkinnedMeshRenderers.push_back( pRenderer );
	}
}