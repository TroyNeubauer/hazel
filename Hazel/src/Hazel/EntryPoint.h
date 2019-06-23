#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#include "Hazel/Context/ContextManager.h"
#include "Hazel/System/Timer.h"

#include <string>

extern Hazel::Application* Hazel::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	Hazel::Timer timer;
	Hazel::Log::Init();
	
	auto app = Hazel::CreateApplication(argc, argv);
	timer.Stop()->Print("Complete initialization took");

	app->Run();
	delete app;

	Hazel::Log::DisableLogging();
	Hazel::ContextManager::Destroy();
}

#endif
