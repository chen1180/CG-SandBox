#pragma once
#include"base/Base.h"
#include"graphics/RenderContext.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
namespace CGCore {
	class OpenGLRenderContext:public RenderContext
	{
	public:
		OpenGLRenderContext(GLFWwindow* windowHandle):m_WindowHandle(windowHandle){};
		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

