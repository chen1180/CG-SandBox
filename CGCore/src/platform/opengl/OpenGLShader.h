#pragma once
#include"graphics/api/Shader.h"
namespace CGCore {
	class OpenGLShader:public Shader
	{
	public:
		OpenGLShader(const char* vertexSource, const char* fragmentSource);
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();
		virtual bool Compile() override;
		virtual void Bind() override;
		virtual void Unbind() override;
	public:
		// Inherited via Shader
		virtual void UploadUniformFloat(const std::string& name, const float& value) override;

		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) override;

		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) override;

		virtual void UploadUniformInt(const std::string& name, const uint32_t& value) override;

		virtual void UploadUniformIntArray(const std::string& name,  int* value, int count) override;

		virtual void UploadUniformMat2(const std::string& name, const glm::mat2& value) override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& value) override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) override;
	private:
		enum ShaderType
		{
			Vertex=0,
			Fragment

		};
		uint32_t Preprocess(const char* source, ShaderType type);
		std::string ReadFile(const std::string& path);
	private:
		uint32_t m_VertexShader, m_FragmentShader;
		uint32_t m_ProgramID;






	};

}

