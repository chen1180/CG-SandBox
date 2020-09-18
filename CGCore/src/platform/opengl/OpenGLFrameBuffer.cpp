#include "pch.h"
#include "OpenGLFrameBuffer.h"
#include<Glad/glad.h>
namespace CGCore {
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecs& framebufferSpecs) :m_FrameBufferSpecs(framebufferSpecs)
	{
		Invalidate();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		glDeleteFramebuffers(1, &m_RendererID);
		//glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}
	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}
	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		m_FrameBufferSpecs.Width = width;
		m_FrameBufferSpecs.Height = height;

		Invalidate();
	}
	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			//glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		switch (m_FrameBufferSpecs.Component)
		{
		case  FrameBufferComponent::Color | FrameBufferComponent::Depth | FrameBufferComponent::Stencil:
			AddColorDepthStencilMap();
			break;
		case FrameBufferComponent::Depth:
			AddDepthMap();
			break;	
		default:
			CG_CORE_ERROR("Unkown Framebuffer Component!");
			break;
		}

		CG_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer Imcomplete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::AddColorDepthStencilMap()
	{
		//Color attachment texture
		Ref<Texture> colorMap = Texture2D::Create(m_FrameBufferSpecs.Width, m_FrameBufferSpecs.Height);
		colorMap->Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorMap->GetID(), 0);
		m_FramebufferData[FrameBufferComponent::Color]=colorMap;

		//Depth attachment texture
		//TODO: Add stencil map in Texture class.
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_FrameBufferSpecs.Width, m_FrameBufferSpecs.Height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
	}
	void OpenGLFrameBuffer::AddDepthMap()
	{
		//Color attachment texture
		Ref<Texture> depthMap = DepthTexture::Create(m_FrameBufferSpecs.Width, m_FrameBufferSpecs.Height);
		depthMap->Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap->GetID(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		m_FramebufferData[FrameBufferComponent::Depth] = depthMap;

	}
}

