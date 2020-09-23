#include "pch.h"
#include "ShadowRenderer.h"
namespace CGCore {
	struct ShadowRendererData {
		std::vector<Ref<Light>> LightSources;
		Ref<Shader> DepthShader;
		FrameBufferSpecs FrameBufferSpecs;
		Ref<FrameBuffer> DepthFrameBuffer;
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
		s_ShadowData->DepthFrameBuffer = FrameBuffer::Create(s_ShadowData->FrameBufferSpecs);
	}
	void ShadowRenderer::ShutDown()
	{
	}
	void ShadowRenderer::BeginScene(const Light& light)
	{
		s_ShadowData->DepthShader->Bind();
		s_ShadowData->DepthFrameBuffer->Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		GLfloat near_plane = 0.1f, far_plane = 100.0f;
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt(glm::vec3(light.Position), glm::vec3(0.0f), glm::vec3(1.0));
		s_ShadowData->DepthShader->UploadUniformMat4("uLightView", lightView);
		s_ShadowData->DepthShader->UploadUniformMat4("uLightProjection", lightProjection);
	}
	void ShadowRenderer::EndScene()
	{
		s_ShadowData->DepthFrameBuffer->Unbind();
	}
	const Ref<Texture>& ShadowRenderer::GetShadowMap()
	{
		 return s_ShadowData->DepthFrameBuffer->GetDepthAttachment(); 
	}
	const Ref<Shader>& ShadowRenderer::GetShader()
	{
		return s_ShadowData->DepthShader;
	}
}