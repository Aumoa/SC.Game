using namespace SC;
using namespace SC::Game;

using namespace System;

Application::Application( AppConfiguration configuration )
{
	if ( configuration.PhysicsUpdatesPerSecond <= 0 )
	{
		configuration.PhysicsUpdatesPerSecond = 60;
	}

	ApplicationCore::mApp = this;
	ApplicationCore::mConfiguration = configuration;

	App::mAppName = msclr::interop::marshal_context().marshal_as<const wchar_t*>( ApplicationCore::mConfiguration.AppName );
	App::mPhysicsHz = ApplicationCore::mConfiguration.PhysicsUpdatesPerSecond;
	App::mVSync = ApplicationCore::mConfiguration.VSync;

	App::Initialize();

	DXGI_ADAPTER_DESC1 desc{ };
	HR( Graphics::mDevice->pAdapter->GetDesc1( &desc ) );

	ApplicationCore::mConfiguration.mAdapterName = String::Format(
		"{0}({1:0.0}GB, {2})",
		msclr::interop::marshal_as<String^>( desc.Description ),
		desc.DedicatedVideoMemory / 1024 / 1024 / 1024,
		( desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE ) > 0 ? "Software" : "Hardware"
	);
}

void Application::OnActive( bool activated )
{

}

int Application::Start( Application^ app )
{
	app->OnStart();

	App::CoreLoop();

	auto ret = app->OnExit();
	App::DisposeAll();

	return ret;
}

void Application::Navigate( UI::Page^ page )
{
	UISystem::mReservedPage = page;
}

void Application::Quit( int exitCode )
{
	PostQuitMessage( exitCode );
}

AppConfiguration Application::Configuration::get()
{
	return ApplicationCore::mConfiguration;
}

UInt32 Application::Width::get()
{
	return mWidth;
}

void Application::Width::set( UInt32 value )
{
	mWidth = value;
}

UInt32 Application::Height::get()
{
	return mHeight;
}

void Application::Height::set( UInt32 value )
{
	mHeight = value;
}