#include "pch.h"
#include "ModelLoader.h"
namespace CGCore {
	Entity ModelLoader::LoadModel(const std::string& path, Scene* scene)
	{
		std::filesystem::path file(path);
		const std::string& fileExtension = file.extension().string();
		
		if (fileExtension == ".obj") {
			return LoadOBJ(path,scene);
		}

	}
}