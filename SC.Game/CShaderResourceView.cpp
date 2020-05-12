using namespace SC;
using namespace SC::Game;

#pragma unmanaged

CShaderResourceView::CShaderResourceView()
{

}

CShaderResourceView::CShaderResourceView( UINT index )
{
	mIndex = index;
}

CShaderResourceView::CShaderResourceView( CShaderResourceView&& right )
{
	mIndex = right.mIndex;
	right.mIndex = -1;
}

CShaderResourceView::~CShaderResourceView()
{
	if ( !App::mDisposed )
	{
		if ( mIndex != -1 )
		{
			DescriptorAllocator::Push( mIndex );
			mIndex = -1;
		}
	}
}

CShaderResourceView& CShaderResourceView::operator=( CShaderResourceView&& right )
{
	if ( mIndex != -1 )
	{
		DescriptorAllocator::Push( mIndex );
		mIndex = -1;
	}

	mIndex = right.mIndex;
	right.mIndex = -1;

	return *this;
}