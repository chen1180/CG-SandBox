#pragma once
#include"CGCore.h"
#include"base/EntryPoint.h"
#include"Sandbox.h"
namespace CGCore {
	class App :public Application {
	public:
		App() {
			PushLayer(new SandBox());
		};
		~App() {};

	};
	Application* CreateApplication()
	{
		return new App();
	}

}