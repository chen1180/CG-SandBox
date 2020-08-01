#include "pch.h"
#include "Renderer.h"
#include"glad/glad.h"
namespace CGCore {
	void Renderer::Init()
	{
	}
	void Renderer::BeginScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 0.0, 0.0, 1.0);

	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit()
	{
	}
}