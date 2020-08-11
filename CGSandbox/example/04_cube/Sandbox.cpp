#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {

	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");


		m_Shader = Shader::Create(std::string("assets/shader/Debug_cube.vert.glsl"), std::string("assets/shader/Debug_cube.frag.glsl"));
		
		auto width=(float)Application::Get().GetWindow().GetWidth();
		auto height= (float)Application::Get().GetWindow().GetHeight();  
		m_Camera = CreateRef<Camera> ( 60.0f, 0.1f, 100.0f, width / height);
		m_Camera->SetCameraControllerType(ControllerType::EditorCamera);
		
		//2D camera
		/*m_Camera = CreateRef<Camera>(width / height, 10.0f);
		m_Camera->SetCameraControllerType(ControllerType::Camera2D);
		*/
		m_Mesh = ModelLoader::LoadModel("assets/mesh/cube.obj");

		
	}
	void SandBox::OnDettach()
	{
	}  
	void SandBox::OnUpdate(float deltaTime)
	{
		m_Camera->GetController()->HandleKeyboard(m_Camera.get(), deltaTime);
		m_Camera->GetController()->HandleMouse(m_Camera.get(), deltaTime,Input::GetMousePosition().first, Input::GetMousePosition().second);
		Renderer::BeginScene();
		m_Shader->Bind();
		m_Shader->UploadUniformMat4("ViewMatrix",  m_Camera->GetViewMatrix());
		m_Shader->UploadUniformMat4("ProjectionMatrix", m_Camera->GetProjectionMatrix());
		m_Mesh->Draw();
	
		Renderer::Submit();
		Renderer::EndScene();
	}
	void SandBox::OnImGuiRender()
	{

		ImGui::Begin("New session"); 
		ImGui::Checkbox("Imgui Demo",&m_ShowImguiDemo);
		if (m_ShowImguiDemo)
			ImGui::ShowDemoWindow(&m_ShowImguiDemo);
		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		m_Camera->OnImGui();
		ImGui::End();
	}

	void SandBox::OnEvent(Event& e) {

	}
} 