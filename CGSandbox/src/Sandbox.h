#pragma once
#include"CGCore.h"
#include"base/EntryPoint.h"
namespace CGCore {

    class Sandbox :public Layer
    {
	public:
		Sandbox():Layer("Sandbox") {}
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
	private:
		GLuint m_Program;
		GLuint m_VAO,m_VBO,m_EBO;
    }; 
	class App :public Application {
	public:
		App() {
			PushLayer(new Sandbox());
		};
		~App() {};

	};
	Application* CreateApplication()
	{
		return new App();
	}

}