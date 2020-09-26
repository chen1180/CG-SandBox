#include "pch.h"
#include "MeshFactory.h"
#include "Mesh.h"
#include"graphics/api/VertexArray.h"
#include"graphics/api/Buffer.h"

namespace CGCore {
	Ref<Mesh> MeshFactory::CreateQuad()
	{
		Vertex* data = new Vertex[4];

		data[0].Position = glm::vec3(-1.0f, -1.0f, 0.0f);
		data[0].TexCoords = glm::vec2(0.0f, 0.0f);
		data[0].Colours =glm::vec4(1.0f);
		data[0].Normal = glm::vec3(0.0f,0.0f,1.0f);

		data[1].Position = glm::vec3(1.0f, -1.0f, 0.0f);
		data[1].Colours = glm::vec4(1.0f);
		data[1].TexCoords = glm::vec2(1.0f, 0.0f);
		data[1].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		data[2].Position = glm::vec3(1.0f, 1.0f, 0.0f);
		data[2].Colours = glm::vec4(1.0f);
		data[2].TexCoords = glm::vec2(1.0f, 1.0f);
		data[2].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		data[3].Position = glm::vec3(-1.0f, 1.0f, 0.0f);
		data[3].Colours = glm::vec4(1.0f);
		data[3].TexCoords = glm::vec2(0.0f, 1.0f);
		data[3].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		
		Ref<VertexArray> va = VertexArray::Create();

		Ref<VertexBuffer> buffer = VertexBuffer::Create(data, sizeof(Vertex) * 4);
		Ref<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(uint32_t) * 6);

		delete[] data;

		BufferLayout layout = {
			{"position",ShaderDataType::Float3},
			{"color",ShaderDataType::Float4},
			{"texCoord",ShaderDataType::Float2},
			{"normal",ShaderDataType::Float3},
			{"tangent",ShaderDataType::Float3}
		};
		buffer->SetLayout(layout);

		va->AddVertexBuffer(buffer);
		va->SetIndexBuffer(ib);

		auto mesh = CreateRef<Mesh>(va, ib);
		return mesh;
	}

	Ref<Mesh> MeshFactory::CreateQuad(float x, float y, float width, float height)
	{
		Vertex* data = new Vertex[4];

		data[0].Position = glm::vec3(x, y, 0.0f);
		data[0].TexCoords = glm::vec2(0.0f, 0.0f);
		data[0].Colours = glm::vec4(1.0f);
		data[0].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		data[1].Position = glm::vec3(x+width,y, 0.0f);
		data[1].Colours = glm::vec4(1.0f);
		data[1].TexCoords = glm::vec2(width, 0.0f);
		data[1].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		data[2].Position = glm::vec3(x + width, y+height, 0.0f);
		data[2].Colours = glm::vec4(1.0f);
		data[2].TexCoords = glm::vec2(width,height);
		data[2].Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		data[3].Position = glm::vec3(x , y+height, 0.0f);
		data[3].Colours = glm::vec4(1.0f);
		data[3].TexCoords = glm::vec2(0.0f, height);
		data[3].Normal = glm::vec3(0.0f, 0.0f,1.0f);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<VertexArray> va = VertexArray::Create();

		Ref<VertexBuffer> buffer = VertexBuffer::Create(data, sizeof(Vertex) * 4);
		Ref<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(uint32_t) * 6);

		delete[] data;

		BufferLayout layout = {
			{"position",ShaderDataType::Float3},
			{"color",ShaderDataType::Float4},
			{"texCoord",ShaderDataType::Float2},
			{"normal",ShaderDataType::Float3},
			{"tangent",ShaderDataType::Float3}
		};
		buffer->SetLayout(layout);

		va->AddVertexBuffer(buffer);
		va->SetIndexBuffer(ib);

		auto mesh = CreateRef<Mesh>(va, ib);
		return mesh;
	}

	Ref<Mesh> MeshFactory::CreatePlane(float width, float height, const glm::vec3& normal)
	{
		return nullptr;
	}
}
