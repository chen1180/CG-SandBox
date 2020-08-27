#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {

	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");
		m_Shader = Shader::Create(std::string("assets/shader/Debug_cube.vert.glsl"), std::string("assets/shader/Debug_cube.frag.glsl"));
		//m_phongShader= Shader::Create(std::string("assets/shader/Phong.vert.glsl"), std::string("assets/shader/Phong.frag.glsl"));
		m_SkyboxShader= Shader::Create(std::string("assets/shader/Debug_skybox.vert.glsl"), std::string("assets/shader/Debug_skybox.frag.glsl"));

		auto width=(float)Application::Get().GetWindow().GetWidth();
		auto height= (float)Application::Get().GetWindow().GetHeight();  
		m_Camera = CreateRef<Camera> ( 60.0f, 0.1f, 100.0f, width / height);
		m_Camera->SetCameraControllerType(ControllerType::MayaCamera);
		//2D camera
		/*m_Camera = CreateRef<Camera>(width / height, 10.0f);
		m_Camera->SetCameraControllerType(ControllerType::Camera2D); 
		*/
		m_Mesh = ModelLoader::LoadModel("assets/mesh/cube.obj");
		m_Cube= ModelLoader::LoadModel("assets/mesh/sphere.obj");
		m_TextureCheckerBoard = Texture2D::Create("assets/texture/Checkerboard.png");
		m_TexturePig= Texture2D::Create("assets/texture/Texture.jpg");
		//cubemap assets
		m_CubeMap = TextureCube::Create("assets/texture/cubemap/skybox");
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		m_skyboxVBO = VertexBuffer::Create(skyboxVertices,sizeof(skyboxVertices));
		BufferLayout layout = { { "position",ShaderDataType::Float3 } };
		m_skyboxVBO->SetLayout(layout);
		m_skyboxVAO = VertexArray::Create();
		m_skyboxVAO->AddVertexBuffer(m_skyboxVBO);
		m_PhongRenderer = PhongRenderer();
		m_PhongRenderer.Init();

	}
	void SandBox::OnDettach()
	{
	}  
	void SandBox::OnUpdate(float deltaTime)
	{
		{
			auto& io=ImGui::GetIO();
			//Camera
			if (!io.WantCaptureMouse) {
				//TODO: move the following functions into event.
				m_Camera->GetController()->HandleKeyboard(m_Camera.get(), deltaTime);
				m_Camera->GetController()->HandleMouse(m_Camera.get(), deltaTime, Input::GetMousePosition().first, Input::GetMousePosition().second);
			}
		
		}
		RenderCommand::Clear();
		RenderCommand::ClearColor();
		{
			m_PhongRenderer.BeginScene(m_Camera.get());
			m_PhongRenderer.SubmitMesh(m_Cube, {1.0,0.0,-3.0});
			m_PhongRenderer.SubmitMesh(m_Mesh, { 2.0,1.0,-3.0 });
			m_PhongRenderer.EndScene();
		}
		{
			//2D
			Renderer2D::Reset2DStats();
			Renderer2D::BeginScene(m_Camera.get());
			Renderer2D::DrawQuad({ 1.0,2.0,3.0f }, { 1.0,1.0 }, m_TextureCheckerBoard);
			Renderer2D::DrawQuad({ 0.5,1.5,2.0f }, { 1.0,1.0 }, m_TexturePig);
			Renderer2D::EndScene();
		}
		{
			//Cubemap

			glDepthFunc(GL_LEQUAL);
			m_SkyboxShader->Bind();
			auto view = glm::mat4(glm::mat3(glm::mat3(m_Camera->GetViewMatrix()))); // remove translation from the view matrix
			m_SkyboxShader->UploadUniformMat4("view", view);
			m_SkyboxShader->UploadUniformMat4("projection", m_Camera->GetProjectionMatrix());
			m_CubeMap->Bind();
			m_skyboxVAO->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDepthFunc(GL_LESS);
		}

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
		//TODO: move this snippet of code to Camera controller class
		//update camera resize
		if (e.GetEventType() == CGCore::EventType::WindowResize) {
			CGCore::WindowResizeEvent& event = (CGCore::WindowResizeEvent&) e;
			float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
			m_Camera->SetAspectRatio(aspectRatio);
		}
	}
} 