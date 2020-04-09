using namespace SC;
using namespace SC::Game;

using namespace System;

Application::Application( AppConfiguration configuration )
{
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

AppConfiguration Application::Configuration::get()
{
	return ApplicationCore::mConfiguration;
}