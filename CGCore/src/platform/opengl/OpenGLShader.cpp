#include "pch.h"
#include "OpenGLShader.h"
#include"glad/glad.h"
#include"glm/gtc/type_ptr.hpp"
namespace CGCore {
	OpenGLShader::OpenGLShader(const char* vertexSource, const char* fragmentSource)
	{
		m_VertexShader = Preprocess(vertexSource, ShaderType::Vertex);
		m_FragmentShader = Preprocess(fragmentSource, ShaderType::Fragment);
		Compile();
	}
	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexShaderSource = ReadFile(vertexPath);
		std::string fragmentShaderSource = ReadFile(fragmentPath);

		m_VertexShader = Preprocess(vertexShaderSource.c_str(), ShaderType::Vertex);
		m_FragmentShader = Preprocess(fragmentShaderSource.c_str(), ShaderType::Fragment);
		Compile();
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
	uint32_t OpenGLShader::GetHandle()
	{
		return m_ProgramID;
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
			CG_CORE_ASSERT(false, "OpenGLShader::ShaderType::Unknown!");
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

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string content;
		std::ifstream fileStream(path, std::ios::in);

		if (!fileStream.is_open()) {
			CG_CORE_ERROR("Could not read file {0}. File does not exist.", path);
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;

	}
	void OpenGLShader::UploadUniformInt(const std::string& name, const uint32_t& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* value, int count)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1iv(location, count,value);
	}
	void OpenGLShader::UploadUniformMat2(const std::string& name, const glm::mat2& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix4fv(location,1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1f(location, value);
	} 
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID,name.c_str());
		glUniform3f(location, value.x,value.y,value.z);
	}
}