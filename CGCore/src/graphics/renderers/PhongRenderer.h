#pragma once
#include "Renderer3D.h"
#include"graphics/api/FrameBuffer.h"
namespace CGCore {
	struct PhongRendererData;
	class PhongRenderer :public Renderer3D
	{
		
	public:
		PhongRenderer() { }
		~PhongRenderer() { }
		virtual void Init() override;
		virtual void ShutDown()override;
		virtual void BeginScene(Camera* camera)override;
		virtual void EndScene()override;

		void SubmitMesh(Ref<Mesh>, const glm::mat4& transform);
		void SubmitLight(const Light& light);
		Ref<FrameBuffer> GetFrameBuffer();
	private:
		static PhongRendererData* s_PhongRenderData;

	};
}

