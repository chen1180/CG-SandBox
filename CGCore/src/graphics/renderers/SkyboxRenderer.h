#pragma once
#include "Renderer3D.h"
namespace CGCore {
	struct SkyboxRendererData;
	class SkyboxRenderer
	{
	public:
		static void Init() ;
		static void ShutDown() ;
		static void BeginScene(Camera* camera) ;
		static void EndScene() ;
	private:
		static SkyboxRendererData* s_SkyboxData;
	};

}
