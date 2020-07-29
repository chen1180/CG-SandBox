#pragma once
#include"base/Base.h"
#include"base/LayerStack.h"
#include"platform/window/WindowsWindow.h"
#include"event/ApplicationEvent.h"
namespace CGCore {

#define BIND_EVENT_FUNC(fn) std::bind(&fn,this,std::placeholders::_1)
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void OnEvent(Event& event);
	private:
		LayerStack m_LayerStack;
		static Application* s_AppInstance;
		Window* m_Window;
		bool m_WindowRunning=true;
		bool m_WindowResize = false;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};
	Application* CreateApplication();
}


