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
		void SubmitMesh(Ref<Mesh>,const glm::vec3& position);
	private:
		static PhongRendererData* s_PhongRenderData;
	};
}

