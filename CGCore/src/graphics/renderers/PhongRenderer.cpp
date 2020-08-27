#include "pch.h"
#include "PhongRenderer.h"
#include"GLFW/glfw3.h"
namespace CGCore {
	struct PhongRendererData {
		static const uint32_t MaxMeshCount = 100;
		static const uint32_t MaxVertex = MaxMeshCount * 1000;
		static const uint32_t MaxIndices = MaxVertex * 3;
		std::vector<Mesh> Meshes;

		Ref<Shader> PhongShader;

		PhongRendererData() = default;
		~PhongRendererData() {
		}
	};

	PhongRendererData* PhongRenderer::s_PhongRenderData = nullptr;
	void PhongRenderer::Init()
	{
		s_PhongRenderData = new PhongRendererData();
		s_PhongRenderData->PhongShader= Shader::Create(std::string("assets/shader/Phong.vert.glsl"), std::string("assets/shader/Phong.frag.glsl"));
		s_PhongRenderData->Meshes.reserve(100);
	}

	void PhongRenderer::ShutDown()
	{
		delete s_PhongRenderData;
	}

	void PhongRenderer::BeginScene(Camera* camera)
	{
		s_PhongRenderData->PhongShader->Bind();
		s_PhongRenderData->PhongShader->UploadUniformMat4("uView", camera->GetViewMatrix());
		s_PhongRenderData->PhongShader->UploadUniformMat4("uProjection", camera->GetProjectionMatrix());
		s_PhongRenderData->PhongShader->UploadUniformFloat3("viewPos", camera->GetPosition());
		//Light TODO: add light class
		s_PhongRenderData->PhongShader->UploadUniformFloat3("lightPos", { 3.0 * sin(glfwGetTime()),5.0,0.0 });
		s_PhongRenderData->PhongShader->UploadUniformFloat3("lightColor", { 1.0,1.0,1.0 });
	}
	void PhongRenderer::SubmitMesh(Ref<Mesh> mesh, const glm::vec3& position)
	{
		s_PhongRenderData->PhongShader->UploadUniformMat4("uModel", glm::translate(glm::mat4(1.0f), position));
		mesh->Draw();
	}
	void PhongRenderer::EndScene()
	{
	}
}

