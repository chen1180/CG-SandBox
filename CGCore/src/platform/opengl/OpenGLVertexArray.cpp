#include "pch.h"
#include "OpenGLVertexArray.h"
namespace CGCore {
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}
		CG_CORE_ASSERT(false, "ShaderDataType::Unknown (Can't convert to OPENGL data type)!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);

	}
	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RenderID);
	}
	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		//if layout is zero, then error
		const auto& layout = vertexBuffer->GetLayout();
		CG_CORE_ASSERT(layout.GetElements().size(), "VertexBuffer layout is zero");
		Bind();
		vertexBuffer->Bind();
		uint32_t index = 0;

		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentSize(), ShaderDataTypeToOpenGLType(element.Type), element.Normalized?GL_TRUE:GL_FALSE, layout.GetStride(), (const void*)(element.Offset));
			index++;	
		}
		Unbind();
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		Unbind();
		m_IndexBuffer = indexBuffer;
	}
	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers()
	{
		return m_VertexBuffers;
	}
	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer()
	{
		return m_IndexBuffer;
	}
}