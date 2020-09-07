#pragma once
#include"Renderer3D.h"
namespace CGCore {
	struct ShadowRendererData;
	class ShadowRenderer :public Renderer3D
	{
	public:
		ShadowRenderer() { Init(); }
		~ShadowRenderer() { ShutDown(); }
		virtual void Init() override;
		virtual void ShutDown() override;
		virtual void BeginScene(Camera* camera) override;
		virtual void EndScene() override;
	private:
		static ShadowRendererData* s_ShadowData;
	};
}

