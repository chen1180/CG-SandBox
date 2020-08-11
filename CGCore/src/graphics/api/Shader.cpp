#include "pch.h"
#include "Shader.h"
#include<graphics/api/RenderAPI.h>
#include"platform/opengl/OpenGLShader.h"
namespace CGCore {
	Ref<Shader> Shader::Create(const char* vertexSource, const char* fragmentSource)
	{
		
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return Ref<Shader>();

	}
	Ref<Shader> Shader::Create(const std::string& vertexSourceFile, const std::string& fragmentSourceFile)
	{
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(vertexSourceFile, fragmentSourceFile);
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return Ref<Shader>();
	}
}