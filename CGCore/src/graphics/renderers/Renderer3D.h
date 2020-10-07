#pragma once
#include"base/Base.h"
#include"graphics/api/Buffer.h"
#include"graphics/api/VertexArray.h"
#include"graphics/api/Shader.h"
#include"graphics/modelLoader/Mesh.h"
#include"graphics/camera/Camera.h"
#include"graphics/Light.h"
#include"graphics/Material.h"
#include"ECS/Component.h"
#include"ECS/Scene.h"
namespace CGCore {
	class Renderer3D
	{
	public:
		virtual ~Renderer3D() {};
		virtual void Init() {};
		virtual void ShutDown() {};
		virtual void BeginScene(Scene* scene) {};
		//TODO:remove later
		virtual void BeginScene(Camera* camera) {};
		virtual void EndScene() {};
		virtual void SetSystemUniformBuffer() {};
	};

}