#include "pch.h"
#include "Renderer.h"
#include"graphics/RenderCommand.h"
namespace CGCore {
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene()
	{
		RenderCommand::Clear();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit()
	{

	}
}