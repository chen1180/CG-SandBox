#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
namespace CGCore {

	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");
		m_Shader = Shader::Create(std::string("assets/shader/Debug_cube.vert.glsl"), std::string("assets/shader/Debug_cube.frag.glsl"));
		m_DepthShader= Shader::Create(std::string("assets/shader/Debug_depth.vert.glsl"), std::string("assets/shader/Debug_depth.frag.glsl"));
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
	
		m_PhongRenderer = PhongRenderer();
		m_Light = CreateRef<Light>(Light(glm::vec3(1.0f) ,glm::vec3(3.0,1.0,-3.0 )));
		m_PhongRenderer.Init();
		m_PhongRenderer.SubmitLight(m_Light);
		for (int i = 0;i < m_Mesh.Meshes.size();i++) {
			m_PhongRenderer.SubmitMesh(m_Mesh.Meshes[i], { 5.0,-0.5,0.0 });
			m_PhongRenderer.SubmitMesh(m_Mesh.Meshes[i], { -2.0,-2.5,0.0 });
			m_PhongRenderer.SubmitMesh(m_Mesh.Meshes[i], { 1.0,-6.5,0.0 });

		}
	
		for (int i = 0;i < m_Cube.Meshes.size();i++) {
			m_PhongRenderer.SubmitMesh(m_Cube.Meshes[i], { 2.0,-0.5,0.0 });

		}

		SkyboxRenderer::Init();

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
			m_PhongRenderer.EndScene();
		}
		{
			//skybox
			SkyboxRenderer::BeginScene(m_Camera.get());
			SkyboxRenderer::EndScene();
		}

	}
	void SandBox::OnImGuiRender()
	{

		ImGui::Begin("New session"); 

		ImGui::Checkbox("Imgui Demo",&m_ShowImguiDemo);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		ImGui::Text("Framebuffer-depth:");
		auto depth = ShadowRenderer::GetShadowMap()->GetID();
		ImGui::Image((void*)depth, { viewportSize.x,viewportSize.y });

		if (m_ShowImguiDemo)
			ImGui::ShowDemoWindow(&m_ShowImguiDemo);
		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		m_Camera->OnImGui();
		ImGui::Separator();
		ImGui::DragFloat3("Light position",&m_Light->Position[0]);
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