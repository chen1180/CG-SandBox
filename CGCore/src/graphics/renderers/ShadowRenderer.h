#pragma once
#include"Renderer3D.h"
#include"graphics/api/FrameBuffer.h"
namespace CGCore {
	struct ShadowRendererData;
	class ShadowRenderer
	{
	public:
		ShadowRenderer() { }
		~ShadowRenderer() { }
		static void Init() ;
		static void ShutDown() ;
		static void BeginScene(const  Ref<Light>& light) ;
		static void EndScene() ;
		static const Ref<Texture>& GetShadowMap();
		static const Ref<Shader>& GetShader();
	private:
		static ShadowRendererData* s_ShadowData;
	};
}

