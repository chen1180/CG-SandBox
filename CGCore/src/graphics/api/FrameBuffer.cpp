#include "pch.h"
#include "FrameBuffer.h"
#include"RenderAPI.h"

#include"platform/opengl/OpenGLFrameBuffer.h"
namespace CGCore {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecs& framebufferSpecs)
	{

		//size in Byte
		switch (RenderAPI::Get())
		{
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(framebufferSpecs);
		case RenderAPI::API::Vulkan:
			break;
		case RenderAPI::API::DirectX:
			break;
		}
		CG_CORE_ASSERT(false, "RenderAPI::API::Unknown");
		return nullptr;
	}
}