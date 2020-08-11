#include "pch.h"
#include "Renderer.h"
#include"graphics/api/RenderCommand.h"
namespace CGCore {
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene()
	{
		RenderCommand::Clear();
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