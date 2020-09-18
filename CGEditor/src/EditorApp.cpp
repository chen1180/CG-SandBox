#pragma once
#include"CGCore.h"
#include"base/EntryPoint.h"
#include"EditorLayer.h"
namespace CGCore {
	class App :public Application {
	public:
		App() {
			PushLayer(new EditorLayer());
		};
		~App() {};

	};
	Application* CreateApplication()
	{
		return new App();
	}

}