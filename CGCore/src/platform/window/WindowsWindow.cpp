#include "pch.h"
#include "WindowsWindow.h"
#include"event/ApplicationEvent.h"
#include"event/MouseEvent.h"
#include"event/KeyEvent.h"
namespace CGCore {
	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProperty& windowProps)
	{
		return new WindowsWindow(windowProps);
	}
	WindowsWindow::WindowsWindow(const WindowProperty& windowProps) 
	{
		Init(windowProps);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProperty& windowProp)
	{
		m_WindowProps.Height = windowProp.Height;
		m_WindowProps.Width = windowProp.Width;
		m_WindowProps.Title = windowProp.Title;
		CG_CORE_INFO("Create a window: {0}x{1}, {2}", m_WindowProps.Width, m_WindowProps.Height, m_WindowProps.Title);
		if (!s_GLFWInitialized) {
			bool success = glfwInit();
			CG_CORE_ASSERT(success, "GLFW failed to initialize!");
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_WindowProps.Width, (int)m_WindowProps.Height, m_WindowProps.Title.c_str(), nullptr, nullptr);

		
		//bind callback function
		glfwSetWindowUserPointer(m_Window, &m_WindowProps);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((uint32_t)x, (uint32_t)y);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key,0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
	
	void WindowsWindow::OnUpdate()
	{

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
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WindowProps.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_WindowProps.VSync;
	}
}