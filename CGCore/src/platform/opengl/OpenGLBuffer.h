#pragma once
#include"graphics/api/Buffer.h"
namespace CGCore{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* data,uint32_t size);
		OpenGLVertexBuffer( uint32_t size);
		// Inherited via VertexBuffer 
		virtual void Bind() override;

		virtual void Unbind() override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

		virtual void SetData(void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() override { return m_Layout; }
	private:
		BufferLayout m_Layout;
		uint32_t m_RenderID;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		// Inherited via VertexBuffer
		virtual void Bind() override;

		virtual void Unbind() override;

		virtual void SetData(unsigned int* data) override;

		virtual uint32_t GetCount() override { return m_Count; };
	private:
		uint32_t m_RenderID;
		uint32_t m_Count=0;
	};

	class OpenGLUniformBuffer :public UniformBuffer {
	public:
		OpenGLUniformBuffer(const void* data, uint32_t size);
		~OpenGLUniformBuffer();
		// Inherited via UniformBuffer
		virtual void Bind(uint32_t slot, Shader* shader, const std::string& name) override;

		virtual void Unbind() override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void UpdateSubData(const void* data, uint32_t size, uint32_t offset) override;

		virtual uint32_t GetCount() override;

		virtual uint32_t GetHandle() override;

	private:
		uint8_t* m_Data = nullptr;
		uint32_t m_Handle;
		uint32_t m_Size = 0;
	};

}


