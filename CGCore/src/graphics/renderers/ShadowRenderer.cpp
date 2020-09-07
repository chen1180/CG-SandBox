#include "pch.h"
#include "ShadowRenderer.h"
namespace CGCore {
	struct ShadowRendererData {
		std::vector<Ref<Light>> LightSources;
		Ref<Shader> PhongShader;

		ShadowRendererData() = default;
		~ShadowRendererData() {
		}
	};
	ShadowRendererData* ShadowRenderer::s_ShadowData = nullptr;
	void ShadowRenderer::Init()
	{
	}
	void ShadowRenderer::ShutDown()
	{
	}
	void ShadowRenderer::BeginScene(Camera* camera)
	{
	}
	void ShadowRenderer::EndScene()
	{
	}
}