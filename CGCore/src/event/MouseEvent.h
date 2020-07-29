#pragma once
#include"Event.h"
namespace CGCore {
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(unsigned int x, unsigned int y)
			: m_XPos(x), m_YPos(y) {}

		uint32_t GetXPosition() const { return m_XPos; }
		uint32_t GetYPosition() const { return m_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePosition: " << m_XPos << ", " << m_YPos;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse|EventCategoryInput)
	private:
		uint32_t m_XPos,m_YPos;
	};


	class MousePressedEvent : public Event
	{
	public:
		MousePressedEvent(int button)
			:m_Button(button) {}

		int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressed: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		int m_Button;
	};

	class MouseReleasedEvent : public Event
	{
	public:
		MouseReleasedEvent(int button)
			:m_Button(button) {}

		int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleased: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		int m_Button;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x,float y)
			:m_XOffset(x), m_YOffset(y) {}

		inline float GetXOffset() { return m_XOffset; }
		inline float GetYOffset() { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse scrolled: " << m_YOffset;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset,m_YOffset;
	};


}