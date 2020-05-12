using namespace FbxSDK;

using namespace System;
using namespace System::Threading;

Importer::Importer()
{
	if ( !mManager )
	{
		mManager = FbxManager::Create();
		mLocker = gcnew Object();
	}

	mImporter = FbxImporter::Create( mManager, "" );
}

Importer::~Importer()
{
	this->!Importer();
}

Importer::!Importer()
{
	if ( mImporter )
	{
		mImporter->Destroy();
		mImporter = nullptr;
	}
}

Scene^ Importer::Import( String^ filepath )
{
	msclr::interop::marshal_context mc;
	auto path = mc.marshal_as<const char*>( filepath );

	Monitor::Enter( mLocker );
	if ( mImporter->Initialize( path ) == false )
	{
		switch ( mImporter->GetStatus().GetCode() )
		{
		case FbxStatus::eInvalidFile:
			throw gcnew IO::FileNotFoundException();
		default:
			throw gcnew Exception( "FBX 파일을 초기화하는 데 실패하였습니다." );
		}
	}

	auto scene = FbxScene::Create( mManager, "scene" );
	if ( mImporter->Import( scene ) == false )
	{
		throw gcnew Exception( "FBX 장면을 초기화하는 데 실패하였습니다." );
	}
	Monitor::Exit( mLocker );

	return gcnew Scene( scene );
}