#pragma once
#include"graphics/Buffer.h"
namespace CGCore{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer( float* data,uint32_t size);
		// Inherited via VertexBuffer 
		virtual void Bind() override;

		virtual void Unbind() override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

		virtual void SetData(float* data) override;

		virtual const BufferLayout& GetLayout() override { return m_Layout; }
	private:
		BufferLayout m_Layout;
		uint32_t m_RenderID;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* data, uint32_t size);
		// Inherited via VertexBuffer
		virtual void Bind() override;

		virtual void Unbind() override;

		virtual void SetData(unsigned int* data) override;
	private:
		uint32_t m_RenderID;
	};

}


