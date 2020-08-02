#pragma once
#include"graphics/Shader.h"
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
	private:
		enum ShaderType
		{
			Vertex=0,
			Fragment

		};
		uint32_t Preprocess(const char* source, ShaderType type);
	private:
		uint32_t m_VertexShader, m_FragmentShader;
		uint32_t m_ProgramID;
	};

}

