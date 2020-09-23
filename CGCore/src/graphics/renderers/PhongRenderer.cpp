#include "pch.h"
#include "PhongRenderer.h"
#include"ShadowRenderer.h"
#include"SkyboxRenderer.h"
#include"GLFW/glfw3.h"
#include"graphics/api/RenderCommand.h"
namespace CGCore {
	struct CommandBuffer {
		Ref<Mesh> Mesh=nullptr;
		glm::mat4 Transform = glm::identity<glm::mat4>();
		CommandBuffer() = default;

	};
	struct PhongRendererData {
		static const uint32_t MaxMeshCount = 100;
		static const uint32_t MaxVertex = MaxMeshCount * 10000;
		static const uint32_t MaxIndices = MaxVertex * 3;
		static const uint32_t MaxNumLight = 32;
		static const uint32_t MaxNumShadowMap = 16;
		std::vector<CommandBuffer> CommandBuffer;
		std::vector<Light> LightSources;
		Ref<Shader> PhongShader;
		Ref<FrameBuffer> FrameBuffer;
		Ref<UniformBuffer> LightUniformBuffer;
		PhongRendererData() = default;
		~PhongRendererData() {
		}
	};

	PhongRendererData* PhongRenderer::s_PhongRenderData = nullptr;
	void PhongRenderer::Init()
	{
		s_PhongRenderData = new PhongRendererData();
		s_PhongRenderData->PhongShader= Shader::Create(std::string("assets/shader/Phong.vert.glsl"), std::string("assets/shader/Phong.frag.glsl"));
		s_PhongRenderData->CommandBuffer.reserve(100);
		s_PhongRenderData->LightSources.reserve(32);

		uint32_t buffersize = s_PhongRenderData->MaxNumLight *sizeof(Light)+sizeof(s_PhongRenderData->MaxNumLight);
		s_PhongRenderData->LightUniformBuffer = UniformBuffer::Create(nullptr, buffersize);
		//TODO: test Shadow renderer, remove in later stage
		ShadowRenderer::Init();
		SkyboxRenderer::Init();
		s_PhongRenderData->FrameBuffer = FrameBuffer::Create(FrameBufferSpecs());
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

		//skybox
		SkyboxRenderer::BeginScene(camera);

		
	
	}

	void PhongRenderer::SubmitMesh(Ref<Mesh> mesh, const glm::mat4& transform)
	{
		CommandBuffer buffer;
		buffer.Mesh = mesh;
		buffer.Transform = transform;
		s_PhongRenderData->CommandBuffer.emplace_back(buffer);
	}
	void PhongRenderer::SubmitLight(const Light& light)
	{
		s_PhongRenderData->LightSources.emplace_back(light);
	}

	 Ref<FrameBuffer> PhongRenderer::GetFrameBuffer()
	{
		return s_PhongRenderData->FrameBuffer;
	}

	void PhongRenderer::EndScene()
	{
		//TODO: remove after shadow test.
		for (auto& light : s_PhongRenderData->LightSources) {
			ShadowRenderer::BeginScene(light);
		}
		//TODO: for temperory test shadow map
		for (auto& command : s_PhongRenderData->CommandBuffer) {
			ShadowRenderer::GetShader()->UploadUniformMat4("uModel", command.Transform);
			command.Mesh->Draw();
		}
		ShadowRenderer::EndScene();


		s_PhongRenderData->PhongShader->Bind(); 
		for (auto& light : s_PhongRenderData->LightSources) {
			//TODO: remove after shadowmap test
			GLfloat near_plane = 0.1f, far_plane = 100.0f;
			glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			glm::mat4 lightView = glm::lookAt(glm::vec3(light.Position), glm::vec3(0.0f), glm::vec3(1.0));
			s_PhongRenderData->PhongShader->UploadUniformMat4("uLightView", lightView);
			s_PhongRenderData->PhongShader->UploadUniformMat4("uLightProjection", lightProjection);
			s_PhongRenderData->PhongShader->UploadUniformFloat3("lightPos", light.Position);
			s_PhongRenderData->PhongShader->UploadUniformFloat3("lightColor", light.Color);
		}
		
		s_PhongRenderData->FrameBuffer->Bind();
		RenderCommand::Clear(); 
		RenderCommand::ClearColor();

		SkyboxRenderer::EndScene();
		//TODO: optisize in the future. Bind shadow map
		s_PhongRenderData->PhongShader->Bind();

		//Light Uniform buffer
		int numLight = s_PhongRenderData->LightSources.size();
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(s_PhongRenderData->LightSources.data(), s_PhongRenderData->LightSources.size()*sizeof(Light),0);
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(&numLight, sizeof(numLight), s_PhongRenderData->MaxNumLight* sizeof(Light));
		s_PhongRenderData->LightUniformBuffer->Bind(0, s_PhongRenderData->PhongShader.get(), "uLights");
	
		ShadowRenderer::GetShadowMap()->Bind(0);
		SkyboxRenderer::GetCubeMap()->Bind(1);
		for (auto& command : s_PhongRenderData->CommandBuffer) {
			s_PhongRenderData->PhongShader->UploadUniformMat4("uModel", command.Transform);
			command.Mesh->Draw(); 
		}

		ShadowRenderer::GetShadowMap()->Unbind();

	}
}

