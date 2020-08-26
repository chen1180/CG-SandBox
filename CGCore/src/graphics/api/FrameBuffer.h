#pragma once
#include"base/Base.h"
namespace CGCore {
	struct FrameBufferSpecs {
		uint32_t Width = 800;
		uint32_t Height = 600;
		uint32_t Samples = 1;

	};
	class FrameBuffer
	{
	public:
		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual const uint32_t& GetRendererID() const = 0;
		virtual const uint32_t& GetColorAttachmentID() const = 0;
		virtual	const uint32_t& GetDepthAttachmentID()const = 0;

		virtual const FrameBufferSpecs& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecs& framebufferSpecs);
	};

}
