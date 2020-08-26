#pragma once
#include"glm/glm.hpp"
#include"event/ApplicationEvent.h"
#include"event/MouseEvent.h"
#include"base/Input.h"
#include"base/KeyCode.h"
#include"base/MouseCode.h"
#include"Camera.h"
namespace CGCore {
	class CameraController {
	public:
		CameraController() = default;
		virtual ~CameraController() = default;

		virtual void HandleMouse(Camera* camera, float dt, float xpos, float ypos) {}
		virtual void HandleKeyboard(Camera* camera, float dt) {}
		virtual void UpdateScroll(Camera* camera, float offset, float dt) { }
		virtual void OnImGui() {}
		void SetMouseSensitivity(float value) { m_MouseSensitivity = value; }

		const glm::vec3& GetVelocity() const { return m_Velocity; }
	
	protected:


		glm::vec3 m_Velocity;
		glm::vec2  m_RotateVelocity;
		glm::vec3 m_FocalPoint;

		float m_ZoomVelocity = 0.0f;
		float m_CameraSpeed = 0.0f;
		float m_Distance = 0.0f;
		float m_Zoom = 1.0f;

		glm::vec2  m_ProjectionOffset= glm::vec2(0.0f);
		glm::vec2 m_PreviousCurserPos = glm::vec2(0.0f, 0.0f);
		float m_MouseSensitivity = 0.1f;

		float m_ZoomDampeningFactor = 0.00001f;
		float m_DampeningFactor = 0.00001f;
		float m_RotateDampeningFactor = 0.00001f;
	};

}