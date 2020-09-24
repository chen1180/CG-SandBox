#include "pch.h"
#include "SkyboxRenderer.h"
#include"graphics/api/Texture.h"
namespace CGCore {
	struct SkyboxRendererData {
		Ref<Shader> SkyboxShader=nullptr;
		Ref<TextureCube> CubeMap= nullptr;
		Ref<VertexArray> SkyboxVAO= nullptr;
		SkyboxRendererData() = default;
		~SkyboxRendererData() {
		}
	};
	SkyboxRendererData* SkyboxRenderer::s_SkyboxData = nullptr;

	void SkyboxRenderer::Init()
	{
		s_SkyboxData = new SkyboxRendererData();
		s_SkyboxData->SkyboxShader = Shader::Create(std::string("assets/shader/Debug_skybox.vert.glsl"), std::string("assets/shader/Debug_skybox.frag.glsl"));
		//cubemap assets
		s_SkyboxData->CubeMap = TextureCube::Create("assets/texture/cubemap/skybox");
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		Ref<VertexBuffer> skyboxVBO;
		skyboxVBO = VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
		BufferLayout layout = { { "position",ShaderDataType::Float3 } };
		skyboxVBO->SetLayout(layout);
		s_SkyboxData->SkyboxVAO = VertexArray::Create();
		s_SkyboxData->SkyboxVAO->AddVertexBuffer(skyboxVBO);
	}
	void SkyboxRenderer::ShutDown()
	{
		delete s_SkyboxData;
	}
	void SkyboxRenderer::BeginScene(Camera* camera)
	{
		glDepthFunc(GL_LEQUAL);
		s_SkyboxData->SkyboxShader->Bind();
		auto view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
		s_SkyboxData->SkyboxShader->UploadUniformMat4("view", view);
		s_SkyboxData->SkyboxShader->UploadUniformMat4("projection", camera->GetProjectionMatrix());
	}
	void SkyboxRenderer::EndScene()
	{
		s_SkyboxData->SkyboxShader->Bind();
		s_SkyboxData->CubeMap->Bind();
		s_SkyboxData->SkyboxVAO->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);
	}
	Ref<TextureCube> SkyboxRenderer::GetCubeMap()
	{
		 return s_SkyboxData->CubeMap; 
	}
	const Ref<Shader>& SkyboxRenderer::GetShader()
	{
		return s_SkyboxData->SkyboxShader;
	}
}
