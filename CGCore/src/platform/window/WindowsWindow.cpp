#include "pch.h"
#include "WindowsWindow.h"
namespace CGCore {
	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProperty& windowProps)
	{
		return new WindowsWindow(windowProps);
	}
	WindowsWindow::WindowsWindow(const WindowProperty& windowProps) :m_WindowProps(windowProps)
	{
		Init(windowProps);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void WindowsWindow::Init(const WindowProperty& windowProp)
	{
		if (!s_GLFWInitialized) {
			bool success = glfwInit();
			CG_CORE_ASSERT(success, "GLFW failed to initialize!");
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_WindowProps.Width, (int)m_WindowProps.Height, m_WindowProps.Title.c_str(), nullptr, nullptr);
	}
	
	void WindowsWindow::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	uint32_t WindowsWindow::GetWidth() const
	{
		return m_WindowProps.Width;
	}
	uint32_t WindowsWindow::GetHeight() const
	{
		return m_WindowProps.Height;
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
}