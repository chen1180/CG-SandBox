#include "pch.h"
#include "MayaCamera.h"
#include "CameraController.h"
namespace CGCore {
	MayaCameraController::MayaCameraController()
	{
		m_PanSpeed = 0.002f;
		m_RotationSpeed = 0.05f;
		m_ZoomSpeed = 0.6f;

		m_RotateVelocity = glm::vec2(0.0f);

		m_FocalPoint = glm::vec3(0.0f);
		glm::vec3 distance = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Distance = distance.length();

		m_RotateDampeningFactor = 0.00001f;
	}

	MayaCameraController::~MayaCameraController()
	{
	}

	void MayaCameraController::HandleMouse(Camera* camera, float dt, float xpos, float ypos)
	{
		const glm::vec2 delta = (glm::vec2(xpos, ypos) - m_PreviousCurserPos);

		if (Input::IsMousePressed(CG_MOUSE_BUTTON_MIDDLE))
			MousePan(camera, delta);
		else if (Input::IsMousePressed(CG_MOUSE_BUTTON_LEFT))
			MouseRotate(delta, dt);
		else if (Input::IsMousePressed(CG_MOUSE_BUTTON_RIGHT))
			MouseZoom(delta.y, dt);

		float yawSign = camera->GetUpDirection().y < 0 ? -1.0f : 1.0f;

		float yaw = camera->GetYaw();
		float pitch = camera->GetPitch();

		yaw += yawSign * m_RotateVelocity.x * dt;
		pitch += m_RotateVelocity.y * dt;

		m_Distance -= m_ZoomVelocity * dt;

		if (m_Distance < 1.0f)
		{
			m_FocalPoint += camera->GetForwardDirection();
			m_Distance = 1.0f;
		}

		m_FocalPoint += camera->GetForwardDirection() * m_ZoomVelocity * dt;

		m_ZoomVelocity = m_ZoomVelocity * pow(m_ZoomDampeningFactor, dt);
		m_RotateVelocity = m_RotateVelocity * pow(m_RotateDampeningFactor, dt);

		if (yaw < 0)
			yaw += 360.0f;

		if (yaw > 360.0f)
			yaw -= 360.0f;

		m_PreviousCurserPos = glm::vec2(xpos, ypos);
		glm::vec3 pos = CalculatePosition(camera);
		camera->SetPosition(pos);
		camera->SetYaw(yaw);
		camera->SetPitch(pitch);
	}

	void MayaCameraController::HandleKeyboard(Camera* camera, float dt)
	{
		//	Camera::HandleKeyboard(dt);
	}
	glm::vec3 MayaCameraController::CalculatePosition(Camera* camera) const
	{
		return m_FocalPoint - camera->GetForwardDirection() * m_Distance;
	}

	void MayaCameraController::MousePan(Camera* camera, const glm::vec2& delta)
	{
		m_FocalPoint += -camera->GetRightDirection() * delta.x * m_PanSpeed * m_Distance;
		m_FocalPoint += camera->GetUpDirection() * delta.y * m_PanSpeed * m_Distance;
	}

	void MayaCameraController::MouseRotate(const glm::vec2& delta, const float dt)
	{
		m_RotateVelocity = m_RotateVelocity + m_RotationSpeed * delta;
	}

	void MayaCameraController::MouseZoom(float delta, const float dt)
	{
		m_ZoomVelocity = m_ZoomVelocity + delta * m_ZoomSpeed;
	}
}

