#include "pch.h"
#include "VertexArray.h"
#include"platform/opengl/OpenGLVertexArray.h"
#include"graphics/api/RenderAPI.h"
namespace CGCore {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return nullptr;
	}

}