#include "pch.h"
#include "Model.h"
namespace CGCore {
	Model::Model(const std::string& filePath)
		: m_FilePath(filePath)
		, m_PrimitiveType(PrimitiveType::File)
	{
		LoadModel(m_FilePath);
	}
	Model::Model(const Ref<Mesh>& mesh, PrimitiveType type)
		: m_FilePath("Primitive")
		, m_PrimitiveType(type)
	{
		m_Meshes.push_back(mesh);
	}

	Model::Model(PrimitiveType type)
		: m_FilePath("Primitive")
		, m_PrimitiveType(type)
	{
		//m_Meshes.push_back(Ref<Mesh>(CreatePrimative(type)));
	}

	void Model::LoadModel(const std::string& path)
	{

		std::filesystem::path file(path);
		const std::string& fileExtension = file.extension().string();

		if (fileExtension == ".obj") {
			LoadOBJ(path);
		}
	}
	void Model::SavePathAndLoadModel(const std::string& path)
	{
		m_Meshes.clear();
		m_FilePath = path;
		LoadModel(m_FilePath);
	}
}
