#pragma once
#include"base/Base.h"

namespace CGCore {
	struct WindowProperty {
		uint32_t Width;
		uint32_t Height;
		std::string Title;
		WindowProperty() :Width(1366), Height(768), Title("Demo") {}
	};
	class Window {
	public:
		virtual ~Window() {};
		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		static Window* Create(const WindowProperty& windowProps=WindowProperty());
		virtual void* GetNativeWindow()const = 0;
	};
}