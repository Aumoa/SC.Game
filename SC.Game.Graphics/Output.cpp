using namespace System;
using namespace System::Drawing;

using namespace SC;
using namespace SC::Game::Graphics::DXGI;

Output::Output()
{

}

Output::~Output()
{
	this->!Output();
}

Output::!Output()
{
	if ( mOutput )
	{
		mOutput->Release();
		mOutput = nullptr;
	}
}

String^ Output::ToString()
{
	auto info = QueryInfo();

	return String::Format( "{0} ({1})", info.DeviceName, info.DesktopCoordinate );
}

OutputQueryInfo Output::QueryInfo()
{
	DXGI_OUTPUT_DESC desc;
	HR( mOutput->GetDesc( &desc ) );

	OutputQueryInfo queryInfo;

	queryInfo.mDeviceName = gcnew String( desc.DeviceName );
	queryInfo.mDesktopCoordinate = System::Drawing::Rectangle( desc.DesktopCoordinates.left, desc.DesktopCoordinates.top, desc.DesktopCoordinates.right - desc.DesktopCoordinates.left, desc.DesktopCoordinates.bottom - desc.DesktopCoordinates.top );
	queryInfo.mRotationMode = ( RotationMode )desc.Rotation;
	queryInfo.mNativeHandle = IntPtr( ( void* )desc.Monitor );

	return queryInfo;
}