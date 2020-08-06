#include "pch.h"
#include "WindowInput.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"base/Application.h"
namespace CGCore {
	Input* Input::s_Input = new WindowInput();
	bool WindowInput::IsKeyPressedImpl(int keycode) {
		auto window =(GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowInput::IsMousePressedImpl(int mousecode) {
		auto window = (GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, mousecode);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowInput::GetMousePositionImpl() {
		auto window = (GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { float(x),float(y) };
	}

}