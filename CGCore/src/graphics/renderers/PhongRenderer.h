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
		virtual void BeginScene(Scene* scene) override;
		virtual void EndScene()override;

		void SubmitMesh(Ref<Mesh> mesh, const glm::mat4& transform);
		void SubmitMesh(Ref<Mesh> mesh,Material mat, const glm::mat4& transform);
		void SubmitLight(const Light& light);
		void OnImguiRender();
		void Reset3DStats();
		Ref<FrameBuffer> GetFrameBuffer();

		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t MeshCount = 0;
			uint32_t LightCount = 0;

		};

	private:
		static PhongRendererData* s_PhongRenderData;

	};
}

