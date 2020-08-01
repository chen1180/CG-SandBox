#pragma once
#include"base/Window.h"
#include"platform/opengl/OpenGLRenderContext.h"
#include<glad/glad.h>
#include <GLFW/glfw3.h>

namespace CGCore {
	class WindowsWindow:public Window
	{
	public:
		WindowsWindow(const WindowProperty& windowProps);
		~WindowsWindow();
		void Init(const WindowProperty& windowProps);
		void ShutDown();
		virtual void OnUpdate() override;
		virtual uint32_t GetWidth()const  override;
		virtual uint32_t GetHeight() const override;
		static Window* Create(const WindowProperty& windowProps = WindowProperty());
		virtual void* GetNativeWindow()const override;

		inline void SetEventCallback(const EventCBFunc& callback) override { m_WindowProps.EventCallback = callback; }
		virtual void SetVSync(bool enabled)override;
		virtual bool IsVSync() const override;

	private:
		GLFWwindow* m_Window;
		OpenGLRenderContext* m_OpenGLContext;
		struct WindowData {
			uint32_t Width, Height;
			std::string Title;
			bool VSync=false;
			EventCBFunc EventCallback;
		};
		WindowData m_WindowProps;
	};

}

