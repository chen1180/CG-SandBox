#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {
	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");

		m_Shader = Shader::Create(std::string("assets/shader/Debug_texture.vert.glsl"), std::string("assets/shader/Debug_texture.frag.glsl"));
		
		BufferLayout layout = {
			{"vertex",ShaderDataType::Float3},{"normal",ShaderDataType::Float2}
		};
		float vertex[] = {
		-0.5,-0.5,0.0,0.0,0.0,
		0.5,-0.5,0.0,1.0,0.0,
		0.5,0.5,0.0,1.0,1.0,
		-0.5,0.5,0.0,0.0,1.0
		};
		unsigned int index[] = { 0,1,2 ,
		0,2,3 };
		//bind VBO
		m_VBO = VertexBuffer::Create(vertex, sizeof(vertex));
		m_VBO->SetLayout(layout);

		m_EBO = IndexBuffer::Create(index, sizeof(index));

		m_VAO = VertexArray::Create();
		
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);
		
		m_Texture = Texture2D::Create("assets/texture/Checkerboard.png");
		
		auto width=(float)Application::Get().GetWindow().GetWidth();
		auto height= (float)Application::Get().GetWindow().GetHeight();
		m_CameraController = new OrthographicsCameraController(width / height);
	}
	void SandBox::OnDettach()
	{
		delete m_CameraController;
	}  
	void SandBox::OnUpdate(float deltaTime)
	{
		m_CameraController->OnUpdate(deltaTime);
		Renderer::BeginScene();
		m_Shader->Bind();
		m_Shader->UploadUniformMat4("ViewProjTransform", m_CameraController->GetCamera().GetViewProjectionMatrix());
		m_Texture->Bind(0);
		m_VAO->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		Renderer::Submit();
		Renderer::EndScene();
	}
	void SandBox::OnImGuiRender()
	{
		ImGui::Begin("New session"); 
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Hello world!");

		ImGui::End();
	}

	void SandBox::OnEvent(Event& e) {
		m_CameraController->OnEvent(e);
	}
} 