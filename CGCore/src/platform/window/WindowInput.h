#pragma once
#include "base/Input.h"
namespace CGCore {
	class WindowInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int mousecode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;

	};


}