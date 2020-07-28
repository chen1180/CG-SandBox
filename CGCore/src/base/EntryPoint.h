#pragma once
#include"CGCore.h"

int main(int argc, char** argv) {
	CGCore::Log::Init();
	auto* app = CGCore::CreateApplication();
	app->Run();
	delete app;
	return 0;
}