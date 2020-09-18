#pragma once
#include"base/Base.h"
#include"Mesh.h"
#include"ECS/Entity.h"
#include"ECS/Scene.h"
#include"ECS/Component.h"
namespace CGCore{
	class VertexArray;
	class ModelLoader
	{
	public:
		static Entity LoadModel(const std::string& path,Scene* scene);
		static Entity LoadOBJ(const std::string& path, Scene* scene);
	};


}