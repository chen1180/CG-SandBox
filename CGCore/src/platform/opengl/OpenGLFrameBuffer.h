#pragma once
#include"graphics/api/FrameBuffer.h"
namespace CGCore {
	class OpenGLFrameBuffer:public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecs& framebufferSpecs);
		~OpenGLFrameBuffer();
		virtual void Bind()const  override;
		virtual void Unbind()const override;
		virtual void Resize(uint32_t width, uint32_t height)override;

		virtual const uint32_t& GetRendererID() const override { return m_RendererID; }
		virtual const uint32_t& GetColorAttachmentID() const override { return m_ColorAttachment; }
		virtual const uint32_t& GetDepthAttachmentID() const override { return m_DepthAttachment; }

		virtual const FrameBufferSpecs& GetSpecification() const override { return m_FrameBufferSpecs; }

		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecs m_FrameBufferSpecs;

	};
}

