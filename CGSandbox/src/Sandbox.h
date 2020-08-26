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
		Ref<Shader> m_Shader,m_phongShader,m_SkyboxShader;
		Ref<Mesh> m_Mesh,m_Cube;
		Ref<Camera> m_Camera;
		Ref<Texture2D> m_TextureCheckerBoard,m_TexturePig;
		Ref<TextureCube> m_CubeMap;
		Ref<VertexBuffer> m_skyboxVBO;
		Ref<VertexArray> m_skyboxVAO;
		bool m_ShowImguiDemo = false;

    }; 

}