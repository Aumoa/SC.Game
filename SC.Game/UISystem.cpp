#pragma unmanaged

using namespace SC;
using namespace SC::Game;
using namespace SC::Game::UI;

using namespace std;

CDeviceContext UISystem::mDeviceContext;
gcroot<UI::Page^> UISystem::mRootPage;
gcroot<UI::Page^> UISystem::mRemovedPages[2];
gcroot<UI::Page^> UISystem::mReservedPage;
gcroot<UI::SolidColorBrush^> UISystem::mDefaultBlackBrush;
gcroot<UI::TextFormat^> UISystem::mDefaultTextFormat;

float UISystem::mWidth;
float UISystem::mHeight;

ComPtr<Heap> UISystem::mConstantBuffer;
D3D12_VIEWPORT UISystem::mViewport;
D3D12_RECT UISystem::mScissorRect;
ComPtr<LargeHeap> UISystem::mShaderDispatchInfo;
UINT UISystem::mShaderDispatchInfoIndex;

set<GlyphBuffer*> UISystem::mGlyphBuffers;
Mutex UISystem::mMutex;
bool UISystem::mDisposed;

#pragma managed

using namespace System;
using namespace System::Drawing;

void UISystem::Initialize()
{
	App::Disposing.push_front( OnDisposing );
	App::Resizing.push_back( OnResizing );

	mDeviceContext = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDefaultBlackBrush = gcnew SolidColorBrush( Color::Black );
	mDefaultBlackBrush->Freeze();
	mDefaultTextFormat = gcnew TextFormat( L"", 15.0f );

	mConstantBuffer = HeapAllocator::Alloc( sizeof( Constants ) );
	mShaderDispatchInfo = new LargeHeap( D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, sizeof( tag_ShaderInfo ) * 8192 );  // 256KB, 8192 glyphs
}

void UISystem::Update( int frameIndex )
{
	if ( mRemovedPages[frameIndex] )
	{
		mRemovedPages[frameIndex] = nullptr;
	}

	if ( mReservedPage )
	{
		auto eventArgs = gcnew UI::NavigationEventArgs( mRootPage, mReservedPage );

		if ( mRootPage )
		{
			mRootPage->OnNavigatedFrom( eventArgs );
		}

		mRootPage.swap( mRemovedPages[frameIndex] );
		mRootPage.swap( mReservedPage );

		mRootPage->OnNavigatedTo( eventArgs );
	}

	if ( auto page = ( Page^ )mRootPage; page )
	{
		RectangleF fullscreen( 0, 0, mWidth, mHeight );

		page->Update( fullscreen );
	}
}

void UISystem::Render( int frameIndex )
{
	// 글리프 렌더링을 시작합니다.
	{
		auto lock = mMutex.Lock();
		for ( auto i : mGlyphBuffers )
		{
			i->LockGlyphs();
			i->Restart();
		}
	}

	// 주 렌더링 컨텍스트는 글리프 렌더링이 완료될 때까지 대기해야 합니다.
	auto pCommandQueue = Graphics::mCoreQueue->pCommandQueue;
	HR( pCommandQueue->Wait( Graphics::mUIQueue->pFence.Get(), Graphics::mUIQueue->mFenceValue ) );

	// 디바이스 컨텍스트를 리셋하고 UI 셰이더를 선택합니다.
	mDeviceContext.Reset( frameIndex, ShaderBuilder::pPipelineStateUI.Get() );
	mDeviceContext.SetGraphicsRootSignature( ShaderBuilder::pRootSignatureUI.Get() );
	mDeviceContext.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// 렌더 타겟을 설정합니다.
	auto index = Graphics::mSwapChain->Index();
	auto pResource = Graphics::mSwapChain->ppBackBuffers[index].Get();
	auto rtv = Graphics::mSwapChain->RTVHandle[index];
	mDeviceContext.OMSetRenderTargets( 1, &rtv, FALSE, nullptr );
	mDeviceContext.RSSetViewports( 1, &mViewport );
	mDeviceContext.RSSetScissorRects( 1, &mScissorRect );

	// 셰이더 입력 매개변수의 인덱스를 초기화합니다.
	mShaderDispatchInfoIndex = 0;

	auto cursorPos = Input::MousePosition;
	float value[2] = { ( float )cursorPos.X, ( float )cursorPos.Y };
	mDeviceContext.SetGraphicsRootConstantBufferView( Slot_UI_ScreenResolution, mConstantBuffer->GetGPUVirtualAddress() );
	mDeviceContext.SetGraphicsRoot32BitConstants( Slot_UI_CursorPos, 2, value );

	if ( auto page = ( Page^ )mRootPage; page )
	{
		page->Render( mDeviceContext );
	}

	mDeviceContext.TransitionBarrier( pResource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, 0 );
	mDeviceContext.Close();

	Graphics::mCoreQueue->Execute( mDeviceContext );
}

void UISystem::OnDisposing()
{
	mDeviceContext.Dispose();
	mRootPage = nullptr;
	delete mDefaultBlackBrush;
	delete mDefaultTextFormat;

	mConstantBuffer.Reset();
	mShaderDispatchInfo.Reset();

	mGlyphBuffers.clear();
	mDisposed = true;
}

void UISystem::OnResizing( int width, int height )
{
	auto block = ( Constants* )mConstantBuffer->Map();
	block->Width = ( float )width;
	block->Height = ( float )height;
	mConstantBuffer->Unmap();

	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mViewport.Width = ( float )width;
	mViewport.Height = ( float )height;
	mViewport.MinDepth = 0;
	mViewport.MaxDepth = 1.0f;

	mScissorRect.left = 0;
	mScissorRect.top = 0;
	mScissorRect.right = width;
	mScissorRect.bottom = height;

	mWidth = ( float )width;
	mHeight = ( float )height;
}