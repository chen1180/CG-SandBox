#pragma once
#include"CGCore.h"
namespace CGCore {

    class SandBox :public Layer
    {
	public:
		SandBox():Layer("Example: Hello square") {}
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
	private:
		Ref<Shader> m_Shader;
		GLuint m_VAO,m_VBO,m_EBO;
    }; 

}