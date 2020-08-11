#pragma once
#include"base/Base.h"
#include"Mesh.h"
namespace CGCore{
	class VertexArray;

	class ModelLoader
	{
	public:
		static Ref<Mesh> LoadModel(const std::string& path);
		static Ref<Mesh> LoadOBJ(const std::string& path);
	};


}