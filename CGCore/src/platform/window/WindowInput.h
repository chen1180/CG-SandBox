#pragma once
#include "base/Input.h"
namespace CGCore {
	class WindowInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int mousecode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual void OnEventImpl(Event& e) override;
		virtual float GetScrollOffsetImpl() override { return m_ScrollOffset; }
		bool OnMouseScrolled(MouseScrolledEvent& e)
		{
			CG_CORE_INFO(e.GetYOffset());
			SetScrollOffsetImpl(e.GetYOffset());
			return false;
		}
		virtual void OnResetImpl()override {
			m_ScrollOffset = 0.0f;
		};
	protected:
		void SetScrollOffsetImpl(float offset) { m_ScrollOffset = offset; }
		
	protected:
		float m_ScrollOffset=0.0f;
	};


}