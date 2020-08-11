#pragma once
#include"base/Base.h"
#include"event/Event.h"
#include"event/MouseEvent.h"
namespace CGCore {
	class Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Input->IsKeyPressedImpl(keycode); }
		inline static bool IsMousePressed(int mousecode) { return s_Input->IsMousePressedImpl(mousecode); }
		inline static  std::pair<float, float> GetMousePosition() { return s_Input->GetMousePositionImpl(); }
		inline static void OnEvent(Event& e) { return s_Input->OnEventImpl(e); }
		inline static void OnReset() { return s_Input->OnResetImpl(); }
		inline static float GetScrollOffset() { return s_Input->GetScrollOffsetImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMousePressedImpl(int mousecode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetScrollOffsetImpl() = 0;
		virtual void OnEventImpl(Event& e) {};
		virtual void OnResetImpl() {};


	private:
		static Input* s_Input;

	};
}