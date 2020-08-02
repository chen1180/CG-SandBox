#include "Sandbox.h"
#include"glad/glad.h"
#include"glm/glm.hpp"
namespace CGCore {
	void Sandbox::OnAttach()
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

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;    
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			CG_CLIENT_WARN("{0}", infoLog.data());
			CG_CLIENT_WARN("OPENGL ERROR::VertexShader: Compilation error!");

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			CG_CLIENT_WARN("{0}", infoLog.data());
			CG_CLIENT_WARN("OPENGL ERROR::FragmentShader: Compilation error!");
			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we 'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			CG_CLIENT_WARN("{0}", infoLog.data());
			CG_CLIENT_WARN("OPENGL ERROR::ShaderProgram: Compilation error!");

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		
		m_Program = program;
		float vertex[] = {
		-0.5,-0.5,0.0,1.0,1.0,0.0,
		0.5,-0.5,0.0,0.0,1.0,0.0,
		0.5,0.5,0.0,0.0,0.1,1.0,
		-0.5,0.5,0.0,0.0,0.0,1.0
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
	void Sandbox::OnDettach()
	{
	}
	void Sandbox::OnUpdate()
	{

		Renderer::BeginScene();
		glUseProgram(m_Program);
		glBindVertexArray(m_VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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