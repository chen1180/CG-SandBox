#include "pch.h"
#include "OpenGLBuffer.h"
namespace CGCore {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void OpenGLVertexBuffer::Bind()
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	void OpenGLVertexBuffer::Unbind()
	{

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(float* data)
	{
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int * data, uint32_t size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void OpenGLIndexBuffer::Bind()
	{

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}
	void OpenGLIndexBuffer::Unbind()
	{

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(unsigned int* data)
	{
	}
}
