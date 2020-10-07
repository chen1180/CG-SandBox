#include"pch.h"
#include "ModelLoader.h"
#include "graphics/api/VertexArray.h"
#include "graphics/api/Buffer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
namespace CGCore {
	Entity ModelLoader::LoadOBJ(const std::string& path, Scene* scene) {

		std::filesystem::path filepath(path);
		std::string error;
		std::string warn;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

	

		bool ok = tinyobj::LoadObj(
			&attrib, &shapes, &materials,&warn, &error,
			path.c_str(),filepath.parent_path().string().c_str()
		);

		if (!ok)
		{
			CG_CORE_ERROR(error);
		}

		std::string name = filepath.filename().string();
		auto entity = scene->CreateEntity(name);
		bool singleMesh = shapes.size() == 1;
	
		
		for (const auto& shape : shapes)
		{
			uint32_t vertexCount = 0;
			const uint32_t numIndices = static_cast<uint32_t>(shape.mesh.indices.size());
			const uint32_t numVertices = numIndices;// attrib.vertices.size();// numIndices / 3.0f;
			Vertex* vertices = new Vertex[numVertices];
			uint32_t* indices = new uint32_t[numIndices];

			std::unordered_map<Vertex, uint32_t> uniqueVertices;

			for (uint32_t i = 0; i < shape.mesh.indices.size(); i++)
			{
				auto& index = shape.mesh.indices[i];
				Vertex vertex;

				if (!attrib.texcoords.empty()) {
					vertex.TexCoords = (
						glm::vec2(
							attrib.texcoords[2 * index.texcoord_index + 0],
							1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
						)
						);
				}
				else
				{
					vertex.TexCoords =
						glm::vec2(0.0f, 0.0f);
				}
				vertex.Position = (
					glm::vec3(
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],
						attrib.vertices[3 * index.vertex_index + 2]
					)
					);

				if (!attrib.normals.empty())
				{
					vertex.Normal = (
						glm::vec3(
							attrib.normals[3 * index.normal_index + 0],
							attrib.normals[3 * index.normal_index + 1],
							attrib.normals[3 * index.normal_index + 2]
						)
						);
				}
				else
				{
					vertex.Normal = (
						glm::vec3(
							0.0f,
							0.0f,
							0.0f
						)
						);
				}

				glm::vec4 colour = glm::vec4(1.0f);

				if (shape.mesh.material_ids[0] >= 0)
				{
					tinyobj::material_t* mp = &materials[shape.mesh.material_ids[0]];
					colour = glm::vec4(mp->diffuse[0], mp->diffuse[1], mp->diffuse[2], 1.0f);
				}

				vertex.Colours = colour;

				if (uniqueVertices.count(vertex) == 0)
				{
					uniqueVertices[vertex] = static_cast<uint32_t>(vertexCount);
					vertices[vertexCount] = vertex;
				}

				indices[vertexCount] = uniqueVertices[vertex];

				vertexCount++;
			}

			/*Ref<Material> pbrMaterial = CreateRef<Material>();

			PBRMataterialTextures textures;

			if (shape.mesh.material_ids[0] >= 0)
			{
				tinyobj::material_t* mp = &materials[shape.mesh.material_ids[0]];

				if (mp->diffuse_texname.length() > 0)
				{
					Ref<Graphics::Texture2D> texture = LoadMaterialTextures("Albedo", m_Textures, mp->diffuse_texname, m_Directory, Graphics::TextureParameters(Graphics::TextureFilter::NEAREST, Graphics::TextureFilter::NEAREST, mp->diffuse_texopt.clamp ? Graphics::TextureWrap::CLAMP_TO_EDGE : Graphics::TextureWrap::REPEAT));
					if (texture)
						textures.albedo = texture;
				}

				if (mp->bump_texname.length() > 0)
				{
					Ref<Graphics::Texture2D> texture = LoadMaterialTextures("Normal", m_Textures, mp->bump_texname, m_Directory, Graphics::TextureParameters(Graphics::TextureFilter::NEAREST, Graphics::TextureFilter::NEAREST, mp->bump_texopt.clamp ? Graphics::TextureWrap::CLAMP_TO_EDGE : Graphics::TextureWrap::REPEAT));
					if (texture)
						textures.normal = texture;//pbrMaterial->SetNormalMap(texture);
				}

				if (mp->roughness_texname.length() > 0)
				{
					Ref<Graphics::Texture2D> texture = LoadMaterialTextures("Roughness", m_Textures, mp->roughness_texname.c_str(), m_Directory, Graphics::TextureParameters(Graphics::TextureFilter::NEAREST, Graphics::TextureFilter::NEAREST, mp->roughness_texopt.clamp ? Graphics::TextureWrap::CLAMP_TO_EDGE : Graphics::TextureWrap::REPEAT));
					if (texture)
						textures.roughness = texture;
				}

				if (mp->metallic_texname.length() > 0)
				{
					Ref<Graphics::Texture2D> texture = LoadMaterialTextures("Metallic", m_Textures, mp->metallic_texname, m_Directory, Graphics::TextureParameters(Graphics::TextureFilter::NEAREST, Graphics::TextureFilter::NEAREST, mp->metallic_texopt.clamp ? Graphics::TextureWrap::CLAMP_TO_EDGE : Graphics::TextureWrap::REPEAT));
					if (texture)
						textures.metallic = texture;
				}

				if (mp->specular_highlight_texname.length() > 0)
				{
					Ref<Graphics::Texture2D> texture = LoadMaterialTextures("Metallic", m_Textures, mp->specular_highlight_texname, m_Directory, Graphics::TextureParameters(Graphics::TextureFilter::NEAREST, Graphics::TextureFilter::NEAREST, mp->specular_texopt.clamp ? Graphics::TextureWrap::CLAMP_TO_EDGE : Graphics::TextureWrap::REPEAT));
					if (texture)
						textures.metallic = texture;
				}
			}

			pbrMaterial->SetTextures(textures);*/

			Ref<VertexArray> va= VertexArray::Create();

			Ref<VertexBuffer> buffer = VertexBuffer::Create( vertices, sizeof(Vertex) * numVertices);
			Ref<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(uint32_t) * numIndices);

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
			if (singleMesh)
			{
				
				entity.AddComponent<MeshComponent>(mesh);
			}
			else {
				//TODO: Add Hierachy component
				auto meshEntity = scene->CreateEntity();
				meshEntity.AddComponent<MeshComponent>(mesh);
				meshEntity.AddComponent<Hierarchy>(entity.GetEntityHandler());
			}

			delete[] vertices;
			delete[] indices;
		}
		return entity;

	}

}