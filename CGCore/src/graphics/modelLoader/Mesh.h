#pragma once
#include<functional>

#include"base/Base.h"
#include"glm/glm.hpp"
#include"graphics/renderers/Renderer.h"
#include"graphics/api/Buffer.h"
#include"graphics/api/VertexArray.h"
namespace CGCore {
	struct BasicVertex
	{
		glm::vec3 Position;
		glm::vec3 color;
		glm::vec2 TexCoords;
	};

	struct Vertex
	{
		Vertex() 
			: Position(glm::vec3(0.0f))
			, Colours(glm::vec4(0.0f))
			, TexCoords(glm::vec2(0.0f))
			, Normal(glm::vec3(0.0f))
			, Tangent(glm::vec3(0.0f))
		{

		}

		glm::vec3  Position;
		glm::vec4  Colours;
		glm::vec2  TexCoords;
		glm::vec3  Normal;
		glm::vec3  Tangent;

		bool operator==(const Vertex& other) const
		{
			return Position == other.Position && TexCoords == other.TexCoords && Colours == other.Colours && Normal == other.Normal && Tangent == other.Tangent;
		}
	};
	class Mesh {
	public:
		Mesh();
		Mesh(const Mesh& mesh);
		Mesh(Ref<VertexArray> vertexArray, Ref<IndexBuffer> indexBuffer);

		virtual ~Mesh();
		virtual void Draw();

		Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
		Ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<IndexBuffer> m_IndexBuffer;

	};

}
namespace std
{
	template<>
	struct hash<glm::vec2>
	{
		size_t operator()(const glm::vec2& x) const
		{
			return hash<float>()(x.x) ^ (hash<float>()(x.y) * 997u);
		}
	};
	template<>
	struct hash<glm::vec3>
	{
		size_t operator()(const glm::vec3& x) const
		{
			return hash<float>()(x.x) ^ (hash<float>()(x.y) * 997u) ^ (hash<float>()(x.z) * 999983u);

		}
	};
	template<>
	struct hash<glm::vec4>
	{
		size_t operator()(const glm::vec4& x) const noexcept
		{
			return hash<float>()(x.x) ^ (hash<float>()(x.y) * 997u) ^ (hash<float>()(x.z) * 999983u) ^ (hash<float>()(x.w) * 999999937);

		}
	};
	template<> struct hash<CGCore::Vertex>
	{
		size_t operator()(CGCore::Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.Position) ^
				(hash<glm::vec2>()(vertex.TexCoords) << 1) ^
				(hash<glm::vec4>()(vertex.Colours) << 1) ^
				(hash<glm::vec3>()(vertex.Normal) << 1) ^
				(hash<glm::vec3>()(vertex.Tangent) << 1)));
		}

	};
}

