#include "pch.h"
#include "Camera.h"
#include"Camera2D.h"
#include"EditorCamera.h"
#include"MayaCamera.h"
#include"imgui/ImguiHelper.h"
namespace CGCore {
	Camera::Camera(float FOV, float Near, float Far, float aspect)
		: m_Pitch(0.0f)
		, m_Yaw(0.0f)
		, m_Roll(0.0f)
		, m_Position(glm::vec3(0.0f, 0.0f, 0.0f))
		, m_AspectRatio(aspect)
		, m_ProjectionDirty(true)
		, m_ViewDirty(true)
		, m_Fov(FOV)
		, m_Near(Near)
		, m_Far(Far)
		, m_Orthographic(false)
		, m_Scale(1.0f)
	{
		
	}

	Camera::Camera(float pitch, float yaw, const glm::vec3& position, float FOV, float Near, float Far, float aspect)
		: m_Pitch(pitch)
		, m_Yaw(yaw)
		, m_Roll(0.0f)
		, m_Position(position)
		, m_AspectRatio(aspect)
		, m_ProjectionDirty(true)
		, m_ViewDirty(true)
		, m_Fov(FOV)
		, m_Near(Near)
		, m_Far(Far)
		, m_Orthographic(false)
		, m_Scale(1.0f)
	{

	}
	Camera::Camera(float aspectRatio, float scale) : m_Pitch(0.0f)
		, m_Yaw(0.0f)
		, m_Roll(0.0f)
		, m_AspectRatio(aspectRatio)
		, m_Scale(scale)
		, m_ProjectionDirty(true)
		, m_ViewDirty(true)
		, m_Fov(0.0f)
		, m_Near(-10.0f)
		, m_Far(10.0f)
		, m_Orthographic(true)
		, m_Position(glm::vec3(0.0f))
	{
	}
	void Camera::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
		ImGui::Columns(2);
		ImGui::Separator();

		ImGuiHelpers::Property("Position", m_Position, -1000.0f, 1000.0f);
		ImGuiHelpers::Property("Aspect", m_AspectRatio, 0.0f, 10.0f);
		ImGuiHelpers::Property("Pitch", m_Pitch, -360.0f, 360.0f);
		ImGuiHelpers::Property("Yaw", m_Yaw, -360.0f, 360.0f);
		ImGuiHelpers::Property("Roll", m_Roll, -360.0f, 360.0f);
		ImGuiHelpers::Property("Fov", m_Fov, 1.0f, 120.0f);
		ImGuiHelpers::Property("Near", m_Near, 0.0f, 10.0f);
		ImGuiHelpers::Property("Far", m_Far, 10.0f, 10000.0f);
		ImGuiHelpers::Property("Zoom", m_Zoom, 0.0f, 100.0f);
		ImGuiHelpers::Property("Offset", m_ProjectionOffset, 0.0f, 10.0f);
		ImGuiHelpers::Property("Scale", m_Scale, 0.0f, 1000.0f);
		ImGui::Checkbox("Orthograhic", &m_Orthographic);

		m_ProjectionDirty = true;
		m_ViewDirty = true;

		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::PopStyleVar();
	}
	const glm::vec3& Camera::GetPosition()
	{
		return m_Position;
	}
	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_ViewDirty = true;
	}
	void Camera::SetMouseSensitivity(float value)
	{
		m_MouseSensitivity = value;
	}
	void Camera::SetIsOrthographic(bool ortho)
	{
		m_ProjectionDirty = true;
		m_Orthographic = ortho;
	}
	bool Camera::IsOrthographic()const
	{
		return m_Orthographic;
	}
	void Camera::SetOrientation(float pitch, float yaw, float roll)
	{
		m_Pitch = pitch;
		m_Yaw = yaw;
		m_Roll = roll;
	}
	float Camera::GetRoll() const
	{
		return m_Roll;
	}
	void Camera::SetRoll(float y)
	{
		m_ViewDirty = true;

		m_Roll = y;
	}
	float Camera::GetYaw() const
	{
		return m_Yaw;
	}
	void Camera::SetYaw(float y)
	{
		m_Yaw = y;
		m_ViewDirty = true;
	}
	float Camera::GetPitch() const
	{
		return m_Pitch;
	}
	void Camera::SetPitch(float p)
	{
		m_Pitch = p;
		m_ViewDirty = true;
	}
	float Camera::GetAspectRatio() const
	{
		return m_AspectRatio;
	}
	void Camera::SetAspectRatio(float y)
	{
		m_AspectRatio = y;
		m_ProjectionDirty = true;
	}
	const glm::mat4& Camera::GetProjectionMatrix()
	{
		if (m_ProjectionDirty)
		{
			UpdateProjectionMatrix();
			m_ProjectionDirty = false;
		}
		return m_ProjMatrix;
	}
	const glm::mat4& Camera::GetViewMatrix()
	{
		if (m_ViewDirty)
		{
			UpdateViewMatrix();
			m_ViewDirty = false;
		}
		return m_ViewMatrix;
	}
	glm::quat Camera::GetOrientation() const
	{
		return  glm::quat(glm::vec3(m_Pitch, m_Yaw, m_Roll));;
	}
	float Camera::GetFar() const
	{
		return m_Far;
	}
	float Camera::GetNear() const
	{
		return m_Near;
	}
	void Camera::SetFar(float pFar)
	{
		m_Far = pFar;
		m_ProjectionDirty = true;
	}
	void Camera::SetNear(float pNear)
	{
		m_Near = pNear;
		m_ProjectionDirty = true;
	}
	float Camera::GetFOV() const
	{
		return m_Fov;
	}
	float Camera::GetScale() const
	{
		return m_Scale;
	}
	void Camera::SetScale(float scale)
	{
		m_Scale = scale;
		m_ProjectionDirty = true;
	}
	glm::vec3 Camera::GetUpDirection() const
	{

		glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
		up = GetOrientation() * up;
		return up;
	}
	glm::vec3 Camera::GetRightDirection() const
	{
		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		right = GetOrientation() * right;
		return right;
	}
	glm::vec3 Camera::GetForwardDirection() const
	{
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
		forward = GetOrientation() * forward;
		return forward;
	}
	void Camera::SetCameraController(const Ref<CameraController>& controller)
	{
		m_CameraController = controller;
	}
	const Ref<CameraController>& Camera::GetController() const
	{
		return m_CameraController;
	}
	void Camera::SetCameraControllerType(ControllerType type)
	{

		m_ControllerType = type;

		switch (type)
		{
		/*case ControllerType::ThirdPerson:
			m_CameraController = CreateRef<ThirdPersonCameraController>();
			break;
		case ControllerType::FPS:
			m_CameraController = CreateRef<FPSCameraController>();
			break;
		case ControllerType::Simple:
			m_CameraController = CreateRef<FPSCameraController>();
			break;*/
		case ControllerType::EditorCamera:
			m_CameraController = CreateRef<EditorCameraController>();
			break;
		case ControllerType::Camera2D:
			m_CameraController = CreateRef<CameraController2D>();
			break;
		case ControllerType::MayaCamera:
			m_CameraController = CreateRef<MayaCameraController>();
			break;
		}
	}
	void Camera::UpdateViewMatrix()
	{
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::mat4(glm::quat(glm::vec3(yaw,pitch,roll)));
		//m_ViewMatrix = glm::inverse(transform);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetForwardDirection(), {0.0,1.0,0.0});
	}
	void Camera::UpdateProjectionMatrix()
	{
		if (m_Orthographic)
			m_ProjMatrix = glm::ortho(-m_AspectRatio * m_Scale, m_AspectRatio * m_Scale, -m_Scale, m_Scale, m_Near, m_Far);
		else
			m_ProjMatrix = glm::perspective( glm::radians(m_Fov), m_AspectRatio,m_Near, m_Far );
	}
}