#pragma once
#include"base/Base.h"
namespace CGCore {
	class Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Input->IsKeyPressedImpl(keycode); }
		inline static bool IsMousePressed(int mousecode) { return s_Input->IsMousePressedImpl(mousecode); }
		inline static  std::pair<float, float> GetMousePosition() { return s_Input->GetMousePositionImpl(); };
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMousePressedImpl(int mousecode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Input;

	};
}