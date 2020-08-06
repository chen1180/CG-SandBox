#include "pch.h"
#include "CameraController.h"
#include"base/KeyCode.h"
namespace CGCore {
	OrthographicsCameraController::OrthographicsCameraController(float aspectRatio) :m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomFactor, aspectRatio* m_ZoomFactor, -m_ZoomFactor, m_ZoomFactor)
	{
	}
	void OrthographicsCameraController::OnUpdate(float ts)
	{
		if (Input::IsKeyPressed(CG_KEY_W))
			m_Position.y += m_CameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(CG_KEY_S))
			m_Position.y -= m_CameraMoveSpeed * ts;
		if (Input::IsKeyPressed(CG_KEY_A))
			m_Position.x -= m_CameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(CG_KEY_D))
			m_Position.x += m_CameraMoveSpeed * ts;

		if (Input::IsKeyPressed(CG_KEY_Q))
			m_Rotation -= m_CameraRotateSpeed * ts;
		if (Input::IsKeyPressed(CG_KEY_E))
			m_Rotation += m_CameraRotateSpeed * ts;

		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_Rotation);

	}
	void OrthographicsCameraController::OnEvent(Event& event)
	{

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(EVENT_CB_FUNC(OrthographicsCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(EVENT_CB_FUNC(OrthographicsCameraController::OnWindowResizedEvent));

	}
	void OrthographicsCameraController::OnResize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomFactor, m_AspectRatio * m_ZoomFactor, -m_ZoomFactor, m_ZoomFactor);
	}
	bool OrthographicsCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{

		m_ZoomFactor -= e.GetYOffset() * 0.25f;
		CG_CORE_INFO("{0}", m_ZoomFactor);
		if (m_ZoomFactor < 0.1f) {
			m_ZoomFactor = 0.1f;
		}

		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomFactor, m_AspectRatio * m_ZoomFactor, -m_ZoomFactor, m_ZoomFactor);
		return false;
	}
	bool OrthographicsCameraController::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		OnResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
