#include "pch.h"
#include "Camera2D.h"

namespace CGCore {
	CameraController2D::CameraController2D() {
		m_Velocity =glm::vec3(0.0f);
		m_MouseSensitivity = 0.005f;
	}
	CameraController2D::~CameraController2D() = default;
	void CameraController2D::HandleMouse(Camera* camera, float dt, float xpos, float ypos)
	{
		if (Input::IsMousePressed(CG_MOUSE_BUTTON_RIGHT))
		{
			glm::vec3 position = camera->GetPosition();
			position.x -= (xpos - m_PreviousCurserPos.x) * camera->GetScale() * m_MouseSensitivity * 0.5f;
			position.y += (ypos - m_PreviousCurserPos.y) * camera->GetScale() * m_MouseSensitivity * 0.5f;
			camera->SetPosition(position);
		}

		m_PreviousCurserPos = glm::vec2(xpos, ypos);
	}
	void CameraController2D::HandleKeyboard(Camera* camera, float dt)
	{
		glm::vec3 up = glm::vec3(0, 1, 0), right = glm::vec3(1, 0, 0);

		m_CameraSpeed = camera->GetScale() * dt * 20.0f;

		if (Input::IsKeyPressed(CG_KEY_A))
		{
			m_Velocity -= right * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(CG_KEY_D))
		{
			m_Velocity += right * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(CG_KEY_W))
		{
			m_Velocity += up * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(CG_KEY_S))
		{
			m_Velocity -= up * m_CameraSpeed;
		}

		if (m_Velocity!=glm::vec3(0.0f))
		{
			glm::vec3 position = camera->GetPosition();
			position += m_Velocity * dt;
			m_Velocity = m_Velocity * pow(m_DampeningFactor, dt);

			camera->SetPosition(position);
		}

		UpdateScroll(camera, Input::GetScrollOffset(), dt);
	}

	void CameraController2D::UpdateScroll(Camera* camera, float offset, float dt)
	{

		float multiplier = 2.0f;
		if (Input::IsKeyPressed(CG_KEY_LEFT_SHIFT))
		{
			multiplier = 10.0f;
		}

		if (offset != 0.0f)
		{
			m_ZoomVelocity += dt * offset * multiplier;
		}

		if (m_ZoomVelocity!=0.0f)
		{
			float scale = camera->GetScale();

			scale -= m_ZoomVelocity;

			if (scale < 0.15f)
			{
				scale = 0.15f;
				m_ZoomVelocity = 0.0f;
			}
			else
			{
				m_ZoomVelocity = m_ZoomVelocity * pow(m_ZoomDampeningFactor, dt);
			}

			camera->SetScale(scale);
		}
	}
}