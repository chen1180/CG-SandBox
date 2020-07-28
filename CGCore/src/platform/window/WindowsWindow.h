#pragma once
#include"base/Window.h"
#include<glad/glad.h>
#include <GLFW/glfw3.h>

namespace CGCore {
	class WindowsWindow:public Window
	{
	public:
		WindowsWindow(const WindowProperty& windowProps);
		void Init(const WindowProperty& windowProps);
		virtual void OnUpdate() override;
		virtual uint32_t GetWidth()const  override;
		virtual uint32_t GetHeight() const override;
		static Window* Create(const WindowProperty& windowProps = WindowProperty());
		virtual void* GetNativeWindow()const override;
	private:
		GLFWwindow* m_Window;
		WindowProperty m_WindowProps;
	};

}

