#pragma once
#include"CGCore.h"
namespace CGCore {

    class EditorLayer :public Layer
    {
	public:
		EditorLayer():Layer("Example: Hello square") {}
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
	private:
		Ref<Shader> m_Shader,m_DepthShader;
		Ref<Camera> m_Camera;
		Ref<Texture2D> m_TextureCheckerBoard,m_TexturePig;
		bool m_ShowImguiDemo = false;
		PhongRenderer m_PhongRenderer;
		Ref<Light> m_Light;
		Ref<Scene> m_Scene;
		float framerate = 0.0f;
    }; 

}