#include "pch.h"
#include "EditorCamera.h"
namespace CGCore {
	EditorCameraController::EditorCameraController()
	{
		
		m_RotateDampeningFactor = 0.0f;
		m_Velocity = glm::vec3(0.0f);
		m_MouseSensitivity = 0.005f;
	}
	EditorCameraController::~EditorCameraController()
	{
	
	}
	void EditorCameraController::HandleMouse(Camera* camera, float dt, float xpos, float ypos)
	{
		if (Input::IsMousePressed(CG_MOUSE_BUTTON_RIGHT))
		{
			m_RotateVelocity = m_RotateVelocity + glm::vec2((xpos - m_PreviousCurserPos.x), (ypos - m_PreviousCurserPos.y)) * m_MouseSensitivity;

			float pitch = camera->GetPitch();
			float yaw = camera->GetYaw();

			pitch -= m_RotateVelocity.y;
			yaw -= m_RotateVelocity.x;

			if (yaw < 0)
			{
				yaw += 360.0f;
			}
			if (yaw > 360.0f)
			{
				yaw -= 360.0f;
			}

			camera->SetYaw(yaw);
			camera->SetPitch(pitch);
				
	
		}

		m_PreviousCurserPos = glm::vec2(xpos, ypos);

		m_RotateVelocity = m_RotateVelocity * pow(m_RotateDampeningFactor, dt);

		UpdateScroll(camera, Input::GetScrollOffset(), dt);
	}
	void EditorCameraController::HandleKeyboard(Camera* camera, float dt)
	{
		float multiplier = 1000.0f;

		if (Input::IsKeyPressed(CG_KEY_LEFT_SHIFT))
		{
			multiplier = 10000.0f;
		}

		m_CameraSpeed = multiplier * dt;

		if (Input::IsMousePressed(CG_MOUSE_BUTTON_RIGHT))
		{
			if (Input::IsKeyPressed(CG_KEY_W))
			{
				m_Velocity -= camera->GetForwardDirection() * m_CameraSpeed;
			}

			if (Input::IsKeyPressed(CG_KEY_S))
			{
				m_Velocity += camera->GetForwardDirection() * m_CameraSpeed;
			}

			if (Input::IsKeyPressed(CG_KEY_A))
			{
				m_Velocity -= camera->GetRightDirection() * m_CameraSpeed;
			}

			if (Input::IsKeyPressed(CG_KEY_D))
			{
				m_Velocity += camera->GetRightDirection() * m_CameraSpeed;
			}

			if (Input::IsKeyPressed(CG_KEY_Q))
			{
				m_Velocity -= camera->GetUpDirection() * m_CameraSpeed;
			}

			if (Input::IsKeyPressed(CG_KEY_E))

				m_Velocity += camera->GetUpDirection() * m_CameraSpeed;
		}

		if (m_Velocity != glm::vec3(0.0f))
		{
			glm::vec3 position = camera->GetPosition();
			position += m_Velocity * dt;
			camera->SetPosition(position);
			m_Velocity = m_Velocity * pow(m_DampeningFactor, dt);
		}


		
	}

	void EditorCameraController::UpdateScroll(Camera* camera, float offset, float dt)
	{
			if (offset != 0.0f)
			{
				m_ZoomVelocity -= dt * offset * 10.0f;
			}

			if (m_ZoomVelocity != 0.0f)
			{
				glm::vec3 pos = camera->GetPosition();
				pos += camera->GetForwardDirection() * m_ZoomVelocity;
				m_ZoomVelocity = m_ZoomVelocity * pow(m_ZoomDampeningFactor, dt);

				camera->SetPosition(pos);
			}
	
	}

}