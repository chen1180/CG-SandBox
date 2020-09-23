#include "pch.h"
#include "OpenGLBuffer.h"
#include"graphics/api/Shader.h"
namespace CGCore {
	//Vertex Buffer
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
	//Index Buffer
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
	
	//Uniform Buffer
	OpenGLUniformBuffer::OpenGLUniformBuffer(const void* data, uint32_t size)
	{
		glGenBuffers(1, &m_Handle);
		m_Data = (uint8_t*)data;
		m_Size = size;
		glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
		glBufferData(GL_UNIFORM_BUFFER, m_Size, m_Data, GL_DYNAMIC_DRAW);

	}
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}
	void OpenGLUniformBuffer::Bind(uint32_t slot, Shader* shader, const std::string& name)
	{
		uint32_t location = glGetUniformBlockIndex(shader->GetHandle(), name.c_str());
		glUniformBlockBinding(shader->GetHandle(), location, slot);
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_Handle);

	}
	void OpenGLUniformBuffer::Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size)
	{
		m_Data = (uint8_t*)data;
		m_Size = size;
		glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
		GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		memcpy(p, m_Data, m_Size);
		glUnmapBuffer(GL_UNIFORM_BUFFER);


	}
	void OpenGLUniformBuffer::UpdateSubData(const void* data, uint32_t size, uint32_t offset)
	{

		m_Data = (uint8_t*)data;
		m_Size = size;
		glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
		GLvoid* p = glMapBufferRange(GL_UNIFORM_BUFFER,offset,m_Size, GL_MAP_WRITE_BIT);
		memcpy(p, m_Data, m_Size);
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
	uint32_t OpenGLUniformBuffer::GetCount()
	{
		return uint32_t();
	}

	uint32_t OpenGLUniformBuffer::GetHandle()
	{
		return m_Handle;
	}

}
