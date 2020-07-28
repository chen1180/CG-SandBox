#include "pch.h"
#include "Application.h"
namespace CGCore {
	Application* Application::s_AppInstance=nullptr;
	Application::Application()
	{
		CG_CORE_ASSERT(!s_AppInstance, "Application already exists!");
		s_AppInstance = this;
		m_Window = Window::Create();
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (true) {
		
			CG_CORE_INFO("App running");
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{ 
		m_LayerStack.PopLayer(layer);
		layer->OnDettach();
	}


}