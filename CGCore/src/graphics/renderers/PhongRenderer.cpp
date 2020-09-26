#include "pch.h"
#include "PhongRenderer.h"
#include"ShadowRenderer.h"
#include"SkyboxRenderer.h"
#include"graphics/api/RenderCommand.h"
#include"GLFW/glfw3.h"
#include"imgui.h"
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
		Ref<UniformBuffer> LightUniformBuffer,TransformUniformBuffer;

		//Statistics
		PhongRenderer::Statistics Stats;
		PhongRendererData() = default;
		~PhongRendererData() {
		}
	};

	PhongRendererData* PhongRenderer::s_PhongRenderData = nullptr;
	void PhongRenderer::Init()
	{
		s_PhongRenderData = new PhongRendererData();
		s_PhongRenderData->PhongShader= Shader::Create(std::string("../assets/shader/Phong.vert.glsl"), std::string("../assets/shader/Phong.frag.glsl"));
		s_PhongRenderData->CommandBuffer.reserve(100);
		s_PhongRenderData->LightSources.reserve(32);

		uint32_t lightBuffersize = s_PhongRenderData->MaxNumLight *sizeof(Light)+sizeof(s_PhongRenderData->MaxNumLight);
		s_PhongRenderData->LightUniformBuffer = UniformBuffer::Create(nullptr, lightBuffersize);
		uint32_t transformBufferSize = sizeof(glm::mat4) * 2;
		s_PhongRenderData->TransformUniformBuffer = UniformBuffer::Create(nullptr, transformBufferSize);

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
		//Init statistics:
		Reset3DStats();
		s_PhongRenderData->PhongShader->Bind();
		//Update Transform Uniform
		s_PhongRenderData->TransformUniformBuffer->UpdateSubData(&camera->GetViewMatrix(),sizeof(glm::mat4),0);
		s_PhongRenderData->TransformUniformBuffer->UpdateSubData(&camera->GetProjectionMatrix(), sizeof(glm::mat4), sizeof(glm::mat4));
		s_PhongRenderData->PhongShader->UploadUniformFloat3("viewPos", camera->GetPosition());
		//Light Uniform buffer
		int numLight = s_PhongRenderData->LightSources.size();
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(s_PhongRenderData->LightSources.data(), s_PhongRenderData->LightSources.size() * sizeof(Light), 0);
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(&numLight, sizeof(numLight), s_PhongRenderData->MaxNumLight * sizeof(Light));
		//Bind uniform buffer
		s_PhongRenderData->TransformUniformBuffer->Bind(0, s_PhongRenderData->PhongShader.get(), "uTransformMatrix");
		s_PhongRenderData->LightUniformBuffer->Bind(1, s_PhongRenderData->PhongShader.get(), "uLights");

		//skybox

		SkyboxRenderer::BeginScene(camera);
		s_PhongRenderData->TransformUniformBuffer->Bind(0, SkyboxRenderer::GetShader().get() , "uTransformMatrix");


		
	
	}

	void PhongRenderer::BeginScene(Scene* scene)
	{

		//Init statistics:
		Reset3DStats();
		s_PhongRenderData->CommandBuffer.clear();
		s_PhongRenderData->LightSources.clear();

		auto& registry = scene->GetRegistry();
		auto view = registry.view<CameraComponent>();
		Camera* mainCamera = nullptr;
		for (auto entity : view) {
			// a component at a time ...
			auto cam = view.get<CameraComponent>(entity);
			if (cam.IsMainCamera) {
				mainCamera = cam.Cam.get();
				break;
			}
		}

		if (mainCamera==nullptr) {
			return;
		}
		
		auto meshview = registry.view<MeshComponent, TransformComponent>();
		for (auto entity : meshview) {
			// a component at a time ...
			auto& meshcomponent = meshview.get<MeshComponent>(entity);
			auto& transformComponent = meshview.get<TransformComponent>(entity);
			SubmitMesh(meshcomponent.Meshes, transformComponent.GetWorldMatrix()*transformComponent.GetLocalMatrix());
		}
		
		auto lightView = registry.view<Light>();
		for (auto entity : lightView) {
			auto& light = lightView.get<Light>(entity);
			SubmitLight(light);
			//TODO: Seperate shadow renderer submit light to a seperate pass
			ShadowRenderer::SubmitLight(light);
		}
		//shadow renderer
		ShadowRenderer::BeginScene(scene);
		
		//Update Transform Uniform
		s_PhongRenderData->PhongShader->Bind();
		s_PhongRenderData->PhongShader->UploadUniformFloat3("viewPos", mainCamera->GetPosition());
		int samplers[16];
		for (int i = 0;i < 16;i++)
			samplers[i] = i;
		s_PhongRenderData->PhongShader->UploadUniformIntArray("shadowMap", samplers, 16);
		
		s_PhongRenderData->TransformUniformBuffer->UpdateSubData(&mainCamera->GetViewMatrix(), sizeof(glm::mat4), 0);
		s_PhongRenderData->TransformUniformBuffer->UpdateSubData(&mainCamera->GetProjectionMatrix(), sizeof(glm::mat4), sizeof(glm::mat4));

		//Light Uniform buffer
		int numLight = s_PhongRenderData->LightSources.size();
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(s_PhongRenderData->LightSources.data(), s_PhongRenderData->LightSources.size() * sizeof(Light), 0);
		s_PhongRenderData->LightUniformBuffer->UpdateSubData(&numLight, sizeof(numLight), s_PhongRenderData->MaxNumLight * sizeof(Light));
		//Bind uniform buffer
		s_PhongRenderData->TransformUniformBuffer->Bind(0, s_PhongRenderData->PhongShader.get(), "uTransformMatrix");
		s_PhongRenderData->LightUniformBuffer->Bind(1, s_PhongRenderData->PhongShader.get(), "uLights");
		ShadowRenderer::GetUniformBuffer()->Bind(2, s_PhongRenderData->PhongShader.get(), "uLightTransformMatrix");

		//skybox
		SkyboxRenderer::BeginScene(mainCamera);
		s_PhongRenderData->TransformUniformBuffer->Bind(0, SkyboxRenderer::GetShader().get(), "uTransformMatrix");

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
		/*for (auto& light : s_PhongRenderData->LightSources) {
			ShadowRenderer::BeginScene(light);
			//TODO: for temperory test shadow map
			for (auto& command : s_PhongRenderData->CommandBuffer) {
				ShadowRenderer::GetShader()->UploadUniformMat4("uModel", command.Transform);
				command.Mesh->Draw();
				s_PhongRenderData->Stats.DrawCalls++;
			}
			ShadowRenderer::EndScene();

		}*/


	
		s_PhongRenderData->FrameBuffer->Bind();
		RenderCommand::Clear(); 
		RenderCommand::ClearColor();
		//TODO: clear up the code here later, very messy!
		auto spec = s_PhongRenderData->FrameBuffer->GetSpecification();
		RenderCommand::OnWindowResize(spec.Width,spec.Height);
		
		//TODO: optisize in the future. Bind shadow map
		s_PhongRenderData->PhongShader->Bind();

		for (int i = 0;i < ShadowRenderer::GetShadowMap().size();i++) {
			ShadowRenderer::GetShadowMap()[i]->GetDepthAttachment()->Bind(i);
		}
		SkyboxRenderer::GetCubeMap()->Bind(ShadowRenderer::GetShadowMap().size()+1);
		
		for (auto& command : s_PhongRenderData->CommandBuffer) {
			s_PhongRenderData->PhongShader->UploadUniformMat4("uModel", command.Transform);
			command.Mesh->Draw(); 
			s_PhongRenderData->Stats.DrawCalls++;
		}
		SkyboxRenderer::EndScene();

	}

	void PhongRenderer::Reset3DStats() {
		memset(&s_PhongRenderData->Stats, 0, sizeof(PhongRenderer::Statistics));
	}

	void PhongRenderer::OnImguiRender() {
		ImGui::Begin("Phong Renderer stats:");
		ImGui::Text("DrawCalls: %d", s_PhongRenderData->Stats.DrawCalls);
		ImGui::Text("Light: %d", s_PhongRenderData->LightSources.size());
		ImGui::Text("Mesh: %d", s_PhongRenderData->CommandBuffer.size());
		ImGui::End();
	}
}

