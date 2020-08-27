#include "pch.h"
#include "Renderer.h"
#include"graphics/api/RenderCommand.h"
#include"Renderer2D.h"
namespace CGCore {
	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::BeginScene()
	{

	}
	void Renderer::DrawIndexed(uint32_t count, const void* start)
	{
		RenderCommand::DrawIndexed(count, start);
	}
	void Renderer::EndScene()
	{
		Renderer2D::EndScene();
	}
	void Renderer::Submit()
	{

	}
	void Renderer::OnWindowReize(uint32_t width, uint32_t height) {
		RenderCommand::OnWindowResize(width, height);
	}
}