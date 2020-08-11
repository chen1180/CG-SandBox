#pragma once
#include"base/Base.h"
#include"graphics/api/VertexArray.h"
#include"graphics/api/Buffer.h"
namespace CGCore {
	class OpenGLVertexArray:public VertexArray
	{
	public:
		OpenGLVertexArray();
		// Inherited via VertexArray
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() override;
	private:
		uint32_t m_RenderID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	
	};


}

