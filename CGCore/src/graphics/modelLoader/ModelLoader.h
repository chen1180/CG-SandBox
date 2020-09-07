#pragma once
#include"base/Base.h"
#include"Mesh.h"
namespace CGCore{
	class VertexArray;

	class ModelLoader
	{
	public:
		static Entity LoadModel(const std::string& path);
		static Entity LoadOBJ(const std::string& path);
	};


}