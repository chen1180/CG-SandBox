#pragma once
#include"event/ApplicationEvent.h"
#include"event/MouseEvent.h"
#include"base/Input.h"
#include"graphics/Camera.h"
namespace CGCore {
	class OrthographicsCameraController {
	public:
		OrthographicsCameraController(float aspectRatio);
		void OnUpdate(float ts);
		void OnEvent(Event& event);

		const OrthographicCamera& GetCamera() const { return m_Camera; }
		OrthographicCamera& GetCamera() { return m_Camera; }

		void SetZoomLevel(float zoomLevel) { m_ZoomFactor = zoomLevel; m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomFactor, m_AspectRatio * m_ZoomFactor, -m_ZoomFactor, m_ZoomFactor); }
		void OnResize(uint32_t width, uint32_t height);

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
	private:
		float m_AspectRatio = 1.0;
		float m_ZoomFactor = 1.0;
		OrthographicCamera m_Camera;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotateSpeed = 10.0f;

	};

}