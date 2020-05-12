using namespace SC;
using namespace SC::Game::Graphics::DXGI;

using namespace System;

OutputEnumerator::OutputEnumerator( Adapter^ adapter )
{
	mAdapter = adapter;
}

OutputEnumerator::~OutputEnumerator()
{
	this->!OutputEnumerator();
}

OutputEnumerator::!OutputEnumerator()
{

}

String^ OutputEnumerator::ToString()
{
	return String::Format( "OutputEnumerator, Current: [{0}]{1}", mCurrent, mCurrentValue );
}

bool OutputEnumerator::MoveNext()
{
	ComPtr<IDXGIOutput> pOutput;
	HRESULT hr = mAdapter->mAdapter->EnumOutputs( ( UINT )++mCurrent, &pOutput );
	if ( hr == DXGI_ERROR_NOT_FOUND )
	{
		return false;
	}

	mCurrentValue = gcnew Output();
	mCurrentValue->mOutput = pOutput.Detach();
	mCurrentValue->mParent = mAdapter;

	return true;
}

void OutputEnumerator::Reset()
{
	mCurrent = -1;
	mCurrentValue = nullptr;
}

Output^ OutputEnumerator::Current::get()
{
	return mCurrentValue;
}

System::Object^ OutputEnumerator::Current2::get()
{
	return mCurrentValue;
}