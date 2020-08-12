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
	}
	void Renderer::Submit()
	{

	}
}