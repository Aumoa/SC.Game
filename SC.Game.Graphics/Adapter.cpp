using namespace SC;
using namespace SC::Game::Graphics::DXGI;

using namespace System;
using namespace System::Collections::Generic;

System::Collections::IEnumerator^ Adapter::GetEnumerator2()
{
	return GetEnumerator();
}

Adapter::Adapter()
{

}

Adapter::~Adapter()
{
	this->!Adapter();
}

Adapter::!Adapter()
{
	if ( mAdapter )
	{
		mAdapter->Release();
		mAdapter = nullptr;
	}
}

String^ Adapter::ToString()
{
	auto info = QueryInfo();

	return String::Format( "{0} (Dedicated VRAM: {1} GiB)", info.Description, ( double )info.DedicatedVideoMemory / 1024 / 1024 / 1024 );
}

IEnumerator<Output^>^ Adapter::GetEnumerator()
{
	return gcnew OutputEnumerator( this );
}

AdapterInfo Adapter::QueryInfo()
{
	DXGI_ADAPTER_DESC1 adapterDesc;
	HR( mAdapter->GetDesc1( &adapterDesc ) );

	AdapterInfo info;
	info.mDescription = gcnew String( adapterDesc.Description );
	info.mVendorId = adapterDesc.VendorId;
	info.mDeviceId = adapterDesc.DeviceId;
	info.mDedicatedVideoMemory = adapterDesc.DedicatedVideoMemory;
	info.mDedicatedSystemMemory = adapterDesc.DedicatedSystemMemory;
	info.mSharedSystemMemory = adapterDesc.SharedSystemMemory;
	info.mSoftware = ( adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE ) == DXGI_ADAPTER_FLAG_SOFTWARE;

	return info;
}