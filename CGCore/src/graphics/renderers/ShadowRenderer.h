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
		static void BeginScene(const  Light& light) ;
		static void BeginScene(Scene* scene);
		static void EndScene() ;
		static void SubmitLight(const Light& light);
		//TODO: Implement in the future
		static void Resize(uint32_t width, uint32_t height);
		static const std::vector<Ref<FrameBuffer>> & GetShadowMap();
		static const Ref<Shader>& GetShader();
		static const Ref<UniformBuffer>& GetUniformBuffer();

	private:
		static ShadowRendererData* s_ShadowData;
	};
}

