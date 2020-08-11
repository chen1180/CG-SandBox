#pragma once
#include"base/Base.h"
#include"glad/glad.h"
#include"graphics/api/Buffer.h"
namespace CGCore {
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const  Ref<IndexBuffer>& GetIndexBuffer() = 0;
		static Ref<VertexArray> Create();
	};
}