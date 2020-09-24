#pragma once
#include "Renderer3D.h"
#include"graphics/api/Texture.h"
namespace CGCore {
	struct SkyboxRendererData;
	class SkyboxRenderer
	{
	public:
		static void Init() ;
		static void ShutDown() ;
		static void BeginScene(Camera* camera) ;
		static void EndScene() ;
		static Ref<TextureCube> GetCubeMap();
		static const Ref<Shader>& GetShader();
	private:
		static SkyboxRendererData* s_SkyboxData;
	};

}
