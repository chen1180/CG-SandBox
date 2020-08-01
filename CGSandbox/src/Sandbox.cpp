#include "Sandbox.h"
#include"glad/glad.h"
namespace CGCore {
	void Sandbox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");
	}
	void Sandbox::OnDettach()
	{
	}
	void Sandbox::OnUpdate()
	{
		Renderer::BeginScene();
		Renderer::Submit();
		Renderer::EndScene();
	}
	void Sandbox::OnImGuiRender()
	{
		ImGui::Begin("New session");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void Sandbox::OnEvent(Event& e) {
	
	}
} 