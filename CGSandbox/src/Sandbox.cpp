#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {
	void SandBox::OnAttach()
	{
		CG_CLIENT_INFO("App layer attached");
		// Read our shaders into the appropriate buffers
		std::string vertexSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
		layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
  
		out vec3 ourColor; // output a color to the fragment shader

		void main()
		{
			gl_Position = vec4(aPos, 1.0);
			ourColor = aColor; // set ourColor to the input color we got from the vertex data
		}     
		)";// Get source code for vertex shader.
		std::string fragmentSource = R"(
		#version 330 core
		out vec4 FragColor;  
		in vec3 ourColor;
  
		void main()
		{
			FragColor = vec4(ourColor, 1.0);
		}
		)"; // Get source code for fragment shader.

		m_Shader = Shader::Create(vertexSource.c_str(),fragmentSource.c_str());
		float vertex[] = {
		-0.5f,-0.5f,0.0f,1.0f,1.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.5f,0.5f,0.0f,0.0f,0.1f,1.0f,
		-0.5f,0.5f,0.0f,0.0f,0.0f,1.0
		};
		unsigned int index[] = { 0,1,2 ,
		0,2,3};
		//bind VBO
		glCreateBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);


		glCreateBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), &index[0], GL_STATIC_DRAW);

		glCreateVertexArrays(1, &m_VAO);
		glBindVertexArray( m_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		
	}
	void SandBox::OnDettach()
	{
	}
	void SandBox::OnUpdate()
	{

		Renderer::BeginScene();
		m_Shader->Bind();
		glBindVertexArray(m_VAO);
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