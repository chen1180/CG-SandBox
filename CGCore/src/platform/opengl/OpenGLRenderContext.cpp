#include "pch.h"
#include "OpenGLRenderContext.h"

namespace CGCore {
	void OpenGLRenderContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		CG_CORE_ASSERT(status, "Failed to initalize Glad!");

		CG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		CG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		CG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLRenderContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}