#include "pch.h"
#include "Buffer.h"
#include"platform/opengl/OpenGLBuffer.h"
#include"RenderAPI.h"
namespace CGCore {
	Ref<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
	{
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(data, size);
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* data, uint32_t size)
	{
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(data, size);
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return nullptr;
	}

}