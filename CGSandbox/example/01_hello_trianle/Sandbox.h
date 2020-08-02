#pragma once
#include"CGCore.h"
namespace CGCore {

    class Layer0 :public Layer
    {
	public:
		Layer0():Layer("Example: Hello square") {}
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
	private:
		GLuint m_Program;
		GLuint m_VAO,m_VBO,m_EBO;
    }; 

}