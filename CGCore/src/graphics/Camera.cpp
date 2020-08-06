#include "pch.h"
#include "Camera.h"
namespace CGCore {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :m_ViewMatrix(1.0), m_ProjectionMatrix(glm::ortho(left, right, bottom, top))
	{

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_Width = right - left;
		m_Height = top - bottom;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{

		m_Position = position;
		RecalculateViewProjMatrix();

	}

	void OrthographicCamera::SetRotation(float rotation)
	{

		m_Rotation = rotation;
		RecalculateViewProjMatrix();
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_Width = right - left;
		m_Height = top - bottom;


		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void OrthographicCamera::RecalculateViewProjMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}