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
			throw gcnew Exception( "FBX ������ �ʱ�ȭ�ϴ� �� �����Ͽ����ϴ�." );
		}
	}

	auto scene = FbxScene::Create( mManager, "scene" );
	if ( mImporter->Import( scene ) == false )
	{
		throw gcnew Exception( "FBX ����� �ʱ�ȭ�ϴ� �� �����Ͽ����ϴ�." );
	}
	Monitor::Exit( mLocker );

	return gcnew Scene( scene );
}