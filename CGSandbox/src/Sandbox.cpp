#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"platform/opengl/OpenGLFrameBuffer.h"
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
		
		m_Scene = CreateRef<Scene>();

		auto cube = ModelLoader::LoadModel("assets/mesh/cube.obj", m_Scene.get());
		auto& transform1 = cube.GetComponent<TransformComponent>();
		transform1.SetWorldMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0, 2.0, 0.0)));

		auto sphere= ModelLoader::LoadModel("assets/mesh/sphere.obj", m_Scene.get());
		auto& transform2 = sphere.GetComponent<TransformComponent>();
		transform2.SetWorldMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f,0.1f,0.1f)));

	//	auto skull= ModelLoader::LoadModel("assets/mesh/12140_Skull_v3_L2.obj", m_Scene.get());
		//transform = sphere.GetComponent<TransformComponent>();
		//transform.SetWorldMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 5.0, 0.0))*glm::scale(glm::mat4(1.0f),glm::vec3(0.1f)));

		//TODO: Add texture component
		m_TextureCheckerBoard = Texture2D::Create("assets/texture/Checkerboard.png");
		m_TexturePig= Texture2D::Create("assets/texture/Texture.jpg");
	
		m_PhongRenderer = PhongRenderer();
		m_Light = CreateRef<Light>(Light(glm::vec3(1.0f) ,glm::vec3(3.0,1.0,-3.0 )));
		m_PhongRenderer.Init();
		m_PhongRenderer.SubmitLight(m_Light);
		
		//TODO: move the following function to renderer
		auto& registry=m_Scene->GetRegistry();
		auto view = registry.view<MeshComponent,TransformComponent>();

		for (auto entity : view) {
			// a component at a time ...
			auto& meshcomponent = view.get<MeshComponent>(entity);
			auto& transformComponent = view.get<TransformComponent>(entity);
			auto posiiton = transformComponent.GetWorldPosition();
			auto scale = transformComponent.GetWorldScale();
			m_PhongRenderer.SubmitMesh(meshcomponent.Meshes, posiiton, scale);
		}
		
		SkyboxRenderer::Init();

	}
	void SandBox::OnDettach()
	{
	}  
	void SandBox::OnUpdate(float deltaTime)
	{
		deltaTime = deltaTime;
		
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
		m_PhongRenderer.GetFrameBuffer()->Unbind();

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

		ImGui::Begin("GameWindow");
		{
			// Using a Child allow to fill all the space of the window.
			// It also alows customization
			ImGui::BeginChild("GameRender");
			
			//Camera
			if (ImGui::IsWindowHovered()) {
				//TODO: move the following functions into event.
				m_Camera->GetController()->HandleKeyboard(m_Camera.get(), deltaTime);
				m_Camera->GetController()->HandleMouse(m_Camera.get(), deltaTime, Input::GetMousePosition().first, Input::GetMousePosition().second);
			}
			// Get the size of the child (i.e. the whole draw size of the windows).
			ImVec2 wsize = ImGui::GetWindowSize();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			glm::vec2 m_FrameBufferSize = { m_PhongRenderer.GetFrameBuffer()->GetSpecification().Width, m_PhongRenderer.GetFrameBuffer()->GetSpecification().Height };
			if (m_FrameBufferSize != *(glm::vec2*) & wsize) {
				CG_CLIENT_INFO("Viewport size: {0} ,{1}", wsize.x, wsize.y);
				m_PhongRenderer.GetFrameBuffer()->Resize(wsize.x, wsize.y);
				m_Camera->SetAspectRatio(wsize.x / wsize.y);

			}
			auto texture =static_cast<OpenGLFrameBuffer*>(m_PhongRenderer.GetFrameBuffer().get());
			ImGui::Image((void*)texture->GetColor(), wsize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
		ImGui::End();
		


	}

	void SandBox::OnEvent(Event& e) {
		//TODO: move this snippet of code to Camera controller class
		//update camera resize
		if (e.GetEventType() == CGCore::EventType::WindowResize) {
			CGCore::WindowResizeEvent& event = (CGCore::WindowResizeEvent&) e;
			float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
			
		}
	}
} 