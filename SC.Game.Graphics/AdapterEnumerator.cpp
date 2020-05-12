using namespace SC;
using namespace SC::Game::Graphics::DXGI;

using namespace System;

AdapterEnumerator::AdapterEnumerator( Factory^ factory )
{
	mFactory = factory;
}

AdapterEnumerator::~AdapterEnumerator()
{
	this->!AdapterEnumerator();
}

AdapterEnumerator::!AdapterEnumerator()
{

}

String^ AdapterEnumerator::ToString()
{
	return String::Format( "AdapterEnumerator, Current: [{0}]{1}", mCurrent, mCurrentValue );
}

bool AdapterEnumerator::MoveNext()
{
	ComPtr<IDXGIAdapter1> pAdapter;
	HRESULT hr = mFactory->mDXGIFactory->EnumAdapters1( ( UINT )++mCurrent, &pAdapter );
	if ( hr == DXGI_ERROR_NOT_FOUND )
	{
		return false;
	}

	mCurrentValue = gcnew Adapter();
	mCurrentValue->mAdapter = pAdapter.Detach();
	mCurrentValue->mParent = mFactory;

	return true;
}

void AdapterEnumerator::Reset()
{
	mCurrent = -1;
	mCurrentValue = nullptr;
}

Adapter^ AdapterEnumerator::Current::get()
{
	return mCurrentValue;
}

System::Object^ AdapterEnumerator::Current2::get()
{
	return mCurrentValue;
}