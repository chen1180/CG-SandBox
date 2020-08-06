#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {
	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");

		m_Shader = Shader::Create(std::string("assets/shader/Debug.vert.glsl"), std::string("assets/shader/Debug.frag.glsl"));
		
		BufferLayout layout = {
			{"vertex",ShaderDataType::Float3},{"color",ShaderDataType::Float3}
		};
		float vertex[] = {
		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f
		};

		unsigned int index[] = { 0,1,2 };
		//bind VBO
		m_VBO = VertexBuffer::Create(vertex, sizeof(vertex));
		m_VBO->SetLayout(layout);

		m_EBO = IndexBuffer::Create(index, sizeof(index));

		m_VAO = VertexArray::Create();
		
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);
		
	}
	void SandBox::OnDettach()
	{
	}  
	void SandBox::OnUpdate(float deltaTime)
	{

		Renderer::BeginScene();
		m_Shader->Bind();
		m_VAO->Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);	
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		Renderer::Submit();
		Renderer::EndScene();
	}
	void SandBox::OnImGuiRender()
	{
		ImGui::Begin("New session");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void SandBox::OnEvent(Event& e) {
	
	}
} 