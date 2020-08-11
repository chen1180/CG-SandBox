#pragma once
#include"base/Base.h"
#include"graphics/layer/LayerStack.h"
#include"platform/window/WindowsWindow.h"
#include"event/ApplicationEvent.h"
#include"imgui/ImguiLayer.h"
#include"Timestep.h"
#include"Input.h"
namespace CGCore {


	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void OnEvent(Event& event);
		
		static Application& Get() { return *s_AppInstance; }
		Window& GetWindow() { return *m_Window; }
	private:
		LayerStack m_LayerStack;
		static Application* s_AppInstance;
		Window* m_Window;
		ImguiLayer* m_ImguiLayer;
		TimeStep m_Time;
		bool m_WindowRunning=true;
		bool m_WindowResize = false;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};
	Application* CreateApplication();
}


