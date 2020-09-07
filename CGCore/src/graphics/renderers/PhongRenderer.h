#pragma once
#include "Renderer3D.h"
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
		void EndScene(Ref<Shader> shader);
		void SubmitMesh(Ref<Mesh>, const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f));
		void SubmitLight(const Ref<Light>& light);
	private:
		static PhongRendererData* s_PhongRenderData;
	};
}

