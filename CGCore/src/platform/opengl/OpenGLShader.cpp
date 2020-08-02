#include "pch.h"
#include "OpenGLShader.h"
#include"glad/glad.h"
namespace CGCore {
	OpenGLShader::OpenGLShader(const char* vertexSource, const char* fragmentSource)
	{
		m_VertexShader = Preprocess(vertexSource, ShaderType::Vertex);
		m_FragmentShader = Preprocess(fragmentSource, ShaderType::Fragment);
		Compile();
	}
	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramID);
	}
	bool OpenGLShader::Compile()
	{

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ProgramID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ProgramID, m_VertexShader);
		glAttachShader(m_ProgramID, m_FragmentShader);

		// Link our program
		glLinkProgram(m_ProgramID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

			CG_CORE_WARN("{0}", infoLog.data());
			CG_CORE_ASSERT(false,"OPENGL ERROR::ShaderProgram: Compilation error!");

			// We don't need the program anymore.
			glDeleteProgram(m_ProgramID);
			// Don't leak shaders either.
			glDeleteShader(m_VertexShader);
			glDeleteShader(m_FragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return false;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_ProgramID, m_VertexShader);
		glDetachShader(m_ProgramID, m_FragmentShader);
		CG_CORE_INFO("OPENGL::ShaderProgram: Compilation successfully!");
		return true;
	}
	void OpenGLShader::Bind()
	{
		glUseProgram(m_ProgramID);
	}
	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}
	uint32_t OpenGLShader::Preprocess(const char* source, ShaderType type)
	{
		// Create an empty vertex shader handle
		uint32_t shaderID=0;
		const char* shaderType = "";
		switch (type)
		{
		case CGCore::OpenGLShader::Vertex:
			shaderID = glCreateShader(GL_VERTEX_SHADER);
			shaderType = "Vertex";
			break;
		case CGCore::OpenGLShader::Fragment:
			shaderID = glCreateShader(GL_FRAGMENT_SHADER);
			shaderType = "Fragment";
			break;
		default:
			CG_CORE_ASSERT(false, "OpenGLShader::ShaderType::Unkown!");
			break;
		}
		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		glShaderSource(shaderID, 1, &source, 0);
		// Compile the vertex shader
		glCompileShader(shaderID);

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
			CG_CORE_WARN("{0}", infoLog.data());
			CG_CORE_ASSERT(false,"OPENGL ERROR::{0}: Compilation error!",shaderType);

			// We don't need the shader anymore.
			glDeleteShader(shaderID);

		}
		CG_CORE_INFO("OPENGL::Shader::{0}: Compilation successfully!", shaderType);
		return shaderID;
	}
}