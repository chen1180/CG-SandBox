#include "pch.h"
#include "Mesh.h"
namespace CGCore {
	Mesh::Mesh() : m_VertexArray(nullptr), m_IndexBuffer(nullptr)
	{
	}
	Mesh::Mesh(const Mesh& mesh) : m_VertexArray(mesh.m_VertexArray), m_IndexBuffer(mesh.m_IndexBuffer)
	{
	}
	Mesh::Mesh(Ref<VertexArray> vertexArray, Ref<IndexBuffer> indexBuffer) : m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer)
	{
	}
	Mesh::~Mesh()
	{
	}
	void Mesh::Draw()
	{
		m_VertexArray->Bind();
		Renderer::DrawIndexed(m_VertexArray->GetIndexBuffer()->GetCount());
		m_VertexArray->Unbind();
	}
}

