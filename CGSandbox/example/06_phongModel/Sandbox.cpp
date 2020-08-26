#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {

	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");


		m_Shader = Shader::Create(std::string("assets/shader/Debug_cube.vert.glsl"), std::string("assets/shader/Debug_cube.frag.glsl"));
		m_phongShader= Shader::Create(std::string("assets/shader/Debug_phong.vert.glsl"), std::string("assets/shader/Debug_phong.frag.glsl"));
		auto width=(float)Application::Get().GetWindow().GetWidth();
		auto height= (float)Application::Get().GetWindow().GetHeight();  
		m_Camera = CreateRef<Camera> ( 60.0f, 0.1f, 100.0f, width / height);
		m_Camera->SetCameraControllerType(ControllerType::MayaCamera);
		
		//2D camera
		/*m_Camera = CreateRef<Camera>(width / height, 10.0f);
		m_Camera->SetCameraControllerType(ControllerType::Camera2D); 
		*/
		m_Mesh = ModelLoader::LoadModel("assets/mesh/sphere.obj");
		m_Cube= ModelLoader::LoadModel("assets/mesh/cube.obj");
		m_TextureCheckerBoard = Texture2D::Create("assets/texture/Checkerboard.png");
		m_TexturePig= Texture2D::Create("assets/texture/Texture.jpg");
	}
	void SandBox::OnDettach()
	{
	}  
	void SandBox::OnUpdate(float deltaTime)
	{
		m_Camera->GetController()->HandleKeyboard(m_Camera.get(), deltaTime);
		m_Camera->GetController()->HandleMouse(m_Camera.get(), deltaTime,Input::GetMousePosition().first, Input::GetMousePosition().second);

		RenderCommand::Clear();
		RenderCommand::ClearColor(glm::vec4(0.0f));
		//3D
		m_phongShader->Bind();
		m_phongShader->UploadUniformMat4("ViewMatrix",  m_Camera->GetViewMatrix());
		m_phongShader->UploadUniformMat4("ProjectionMatrix", m_Camera->GetProjectionMatrix());
		m_phongShader->UploadUniformMat4("ModelMatrix", glm::translate(glm::mat4(1.0f),glm::vec3(0.5,0.5,-3.0f)));
		m_phongShader->UploadUniformFloat3("lightPos", {3.0*sin(glfwGetTime()),5.0,0.0});
		m_phongShader->UploadUniformFloat3("lightColor", { 1.0,1.0,1.0 });
		m_phongShader->UploadUniformFloat3("viewPos", m_Camera->GetPosition());
		m_phongShader->UploadUniformFloat3("objectColor", { 0.0,0.0,1.0 });
		m_Mesh->Draw();
		m_phongShader->UploadUniformMat4("ModelMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(-2.0, 0.5, -3.0f)));
		m_Cube->Draw();
		//2D
		Renderer2D::Reset2DStats();
		Renderer2D::BeginScene(m_Camera.get());
		Renderer2D::DrawQuad({ 1.0,2.0,3.0f }, { 1.0,1.0 }, m_TextureCheckerBoard);
		Renderer2D::DrawQuad({ 0.5,1.5,2.0f }, { 1.0,1.0 }, m_TexturePig);
		Renderer2D::EndScene();



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
		Renderer2D::OnImguiRender();
	}

	void SandBox::OnEvent(Event& e) {

	}
} 