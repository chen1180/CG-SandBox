#include "pch.h"
#include "Application.h"
#include"graphics/renderers/Renderer.h"

namespace CGCore {

	Application* Application::s_AppInstance=nullptr;
	Application::Application()
	{
		CG_CORE_ASSERT(!s_AppInstance, "Application already exists!");
		s_AppInstance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(EVENT_CB_FUNC(Application::OnEvent));
		m_ImguiLayer = new ImguiLayer();
		PushLayer(m_ImguiLayer);
		//init renderer
		Renderer::Init();
	}
	Application::~Application()
	{
		delete m_Window;
	}
	void Application::Run()
	{
		while (m_WindowRunning) {
			if (!m_WindowResize) {
				float deltaTime = m_Time.UpdateDeltaTime((float)glfwGetTime());
				//update layer
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(deltaTime);
				}
				//imgui layer
				m_ImguiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
				m_ImguiLayer->End();
			}
			//TODO: remove later
			//reset input 
			Input::OnReset();

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

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_WindowRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_WindowResize = true;
			return false;

		}
		Renderer::OnWindowReize(e.GetWidth(), e.GetHeight());
		m_WindowResize = false;
		return false;
	}

	void  Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_CB_FUNC(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(EVENT_CB_FUNC(Application::OnWindowResize));
		CG_CORE_INFO(event.ToString());
		
		for (auto it = m_LayerStack.begin();it != m_LayerStack.end();it++) {
			if (event.Handled)
				break;
			(*it)->OnEvent(event);
		}
		Input::OnEvent(event);


	}

}