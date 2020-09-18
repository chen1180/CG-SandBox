#pragma once
#include"base/Base.h"
#include"graphics/api/Texture.h"
namespace CGCore {
	enum FrameBufferComponent{
		Color=BIT(0),
		Depth=BIT(1),
		Stencil=BIT(2)
	};

	struct FrameBufferSpecs {
		uint32_t Width = 800;
		uint32_t Height = 600;
		uint32_t Samples = 1;
		uint8_t Component = FrameBufferComponent::Color | FrameBufferComponent::Depth | FrameBufferComponent::Stencil;
	};
	class FrameBuffer
	{
	public:
		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual const uint32_t& GetRendererID() const = 0;
		virtual const Ref<Texture>& GetColorAttachment() const = 0;
		virtual	const  Ref<Texture>& GetDepthAttachment()const = 0;

		virtual const FrameBufferSpecs& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecs& framebufferSpecs);
	};

}
