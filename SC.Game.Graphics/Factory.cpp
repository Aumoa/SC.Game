using namespace System;
using namespace System::Collections::Generic;

using namespace SC;
using namespace SC::Game::Graphics::DXGI;

System::Collections::IEnumerator^ Factory::GetEnumerator2()
{
	return GetEnumerator();
}

Factory::Factory()
{
	ComPtr<IDXGIFactory7> pFactory;

	CreateDXGIFactory( IID_PPV_ARGS( &pFactory ) );
	this->mDXGIFactory = pFactory.Detach();
}

Factory::~Factory()
{
	this->!Factory();
}

Factory::!Factory()
{
	if ( mDXGIFactory )
	{
		mDXGIFactory->Release();
		mDXGIFactory = nullptr;
	}
}

IEnumerator<Adapter^>^ Factory::GetEnumerator()
{
	return gcnew AdapterEnumerator( this );
}