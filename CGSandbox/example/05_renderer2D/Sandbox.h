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
		Ref<Mesh> m_Mesh;
		Ref<Camera> m_Camera;
		Ref<Texture2D> m_Texture;
		bool m_ShowImguiDemo = false;
    }; 

}