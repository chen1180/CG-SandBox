#include "pch.h"
#include "ShadowRenderer.h"
#include "graphics/api/RenderCommand.h"
namespace CGCore {
	struct ShadowRendererData {
		static const uint32_t MaxNumShadowMap = 16;
		std::vector<Light> LightSources;
		Ref<Shader> DepthShader;
		FrameBufferSpecs FrameBufferSpecs;
		std::vector<Ref<FrameBuffer>> ShadowMaps;
		Ref<UniformBuffer> LightTransformUBuffer;
		ShadowRendererData() = default;
		~ShadowRendererData() {
		}
	};
	ShadowRendererData* ShadowRenderer::s_ShadowData = nullptr;
	void ShadowRenderer::Init()
	{
		s_ShadowData = new ShadowRendererData();
		s_ShadowData->DepthShader=Shader::Create(std::string("assets/shader/Debug_depth.vert.glsl"), std::string("assets/shader/Debug_depth.frag.glsl"));
		
		s_ShadowData->FrameBufferSpecs = FrameBufferSpecs();
		s_ShadowData->FrameBufferSpecs.Component = FrameBufferComponent::Depth;
		s_ShadowData->FrameBufferSpecs.Width = 1200;
		s_ShadowData->FrameBufferSpecs.Height = 800;
		
		s_ShadowData->LightSources.reserve(32);
		s_ShadowData->ShadowMaps.reserve(16);
		
		for (int i = 0;i < ShadowRendererData::MaxNumShadowMap;i++) {
			s_ShadowData->ShadowMaps.emplace_back(FrameBuffer::Create(s_ShadowData->FrameBufferSpecs));
		}
		// 16* LightViewProjectionMatrix + index
		uint32_t bufferSize = ShadowRendererData::MaxNumShadowMap * ShaderDataTypeSize(ShaderDataType::Mat4)  + ShaderDataTypeSize(ShaderDataType::Int);
		s_ShadowData->LightTransformUBuffer = UniformBuffer::Create(nullptr, bufferSize);
	}
	void ShadowRenderer::ShutDown()
	{
		delete s_ShadowData;
	}
	void ShadowRenderer::BeginScene(const Light& light)
	{
		/*s_ShadowData->DepthShader->Bind();
		s_ShadowData->ShadowMaps->Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		GLfloat near_plane = 0.1f, far_plane = 100.0f;
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt(glm::vec3(light.Position), glm::vec3(0.0f), glm::vec3(1.0));
		s_ShadowData->DepthShader->UploadUniformMat4("uLightView", lightView);
		s_ShadowData->DepthShader->UploadUniformMat4("uLightProjection", lightProjection);
		*/
	}
	void ShadowRenderer::BeginScene(Scene* scene)
	{
		s_ShadowData->DepthShader->Bind();
		uint32_t offset = 0;
		for (int i = 0;i < s_ShadowData->LightSources.size();i++) {
			auto& light = s_ShadowData->LightSources[i];

			s_ShadowData->ShadowMaps[i]->Bind();
			glClear(GL_DEPTH_BUFFER_BIT);
			GLfloat near_plane = 0.1f, far_plane = 10.5f;
			glm::mat4 lightViewProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane) * glm::lookAt(glm::vec3(light.Position), glm::vec3(light.Direction), glm::vec3(0.0f,1.0f,0.0f));
			s_ShadowData->LightTransformUBuffer->UpdateSubData(&lightViewProjection, sizeof(glm::mat4), offset);
			offset += sizeof(glm::mat4);
			s_ShadowData->ShadowMaps[i]->Unbind();
		}
		int size = s_ShadowData->LightSources.size();
		s_ShadowData->LightTransformUBuffer->UpdateSubData(&size, sizeof(int), sizeof(glm::mat4)*s_ShadowData->MaxNumShadowMap);

		//TODO: seperate beginscene to smaller group
		s_ShadowData->LightTransformUBuffer->Bind(0,s_ShadowData->DepthShader.get(),"uLightTransformMatrix");
		glCullFace(GL_FRONT);
		auto& registry = scene->GetRegistry();
		for (int i = 0;i < s_ShadowData->LightSources.size();i++) {
			auto texture = s_ShadowData->ShadowMaps[i]->GetDepthAttachment();

			s_ShadowData->ShadowMaps[i]->Bind();
			RenderCommand::OnWindowResize(texture->GetWidth(), texture->GetHeight());
			auto meshview = registry.view<Model, TransformComponent>();
			for (auto entity : meshview) {
				// a component at a time ...
				auto& model = meshview.get<Model>(entity);
				auto& transformComponent = meshview.get<TransformComponent>(entity);
				s_ShadowData->DepthShader->UploadUniformInt("uLightIndex", i);
				s_ShadowData->DepthShader->UploadUniformMat4("uModel", transformComponent.GetWorldMatrix() * transformComponent.GetLocalMatrix());
				for(auto& mesh: model.GetMeshes())
					mesh->Draw();
			}
			s_ShadowData->ShadowMaps[i]->Unbind();
		}
		glCullFace(GL_BACK);
		s_ShadowData->LightSources.clear();

	}
	void ShadowRenderer::EndScene()
	{
		//s_ShadowData->ShadowMaps->Unbind();
	}
	void ShadowRenderer::SubmitLight(const Light& light)
	{
		s_ShadowData->LightSources.emplace_back(light);
	}

	void ShadowRenderer::Resize(uint32_t width, uint32_t height)
	{
		for (int i =0; i< s_ShadowData->ShadowMaps.size();i++)
		{

			s_ShadowData->ShadowMaps[i]->Resize(width, height);
		}
	}

	const std::vector<Ref<FrameBuffer>>& ShadowRenderer::GetShadowMap()
	{
		 return s_ShadowData->ShadowMaps; 
	}
	const Ref<Shader>& ShadowRenderer::GetShader()
	{
		return s_ShadowData->DepthShader;
	}
	const Ref<UniformBuffer>& ShadowRenderer::GetUniformBuffer()
	{
		return s_ShadowData->LightTransformUBuffer;
	}
}