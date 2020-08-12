#include "pch.h"
#include "OpenGLBuffer.h"
namespace CGCore {
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	void OpenGLVertexBuffer::Bind()
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	void OpenGLVertexBuffer::Unbind()
	{

		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}
	void OpenGLVertexBuffer::SetData(void* data,uint32_t size)
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		m_Count = size / sizeof(uint32_t);
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
