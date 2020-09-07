#include "pch.h"
#include "ModelLoader.h"
namespace CGCore {
	Entity ModelLoader::LoadModel(const std::string& path)
	{
		std::filesystem::path file(path);
		const std::string& fileExtension = file.extension().string();
		
		if (fileExtension == ".obj") {
			return LoadOBJ(path);
		}

	}
}