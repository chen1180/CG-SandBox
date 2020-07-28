#pragma once
#include"base/Base.h"
#include"base/LayerStack.h"
namespace CGCore {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		LayerStack m_LayerStack;
		static Application* s_AppInstance;
	};
	Application* CreateApplication();
}


