#pragma once
#include"CGCore.h"
namespace CGCore {

    class SandBox :public Layer
    {
	public:
		SandBox():Layer("Example: Hello square") {}
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
	private:
		Ref<Shader> m_Shader;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_EBO;
		Ref<VertexArray> m_VAO;

    }; 

}