#include "pch.h"
#include "OpenGLRenderAPI.h"
#include"glad/glad.h"
namespace CGCore {
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.7f, 0.3f, 0.4f, 1.0f);
	}
	void OpenGLRenderAPI::DrawIndexed(uint32_t count, const void* start)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, start);
	}

}
