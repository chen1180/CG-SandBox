#pragma once
#include"base/Base.h"
#include"math/Math.h"

#include <cereal/cereal.hpp>
namespace CGCore {
	enum class ControllerType {
		FPS=0,
		ThirdPerson,
		Simple,
		Camera2D,
		EditorCamera,
		MayaCamera
	};

	/*enum RenderPath
	{
		Forward=0,
		Deferred,
		Batch2D
	};

	enum  RenderTarget
	{
		Texture=0,
		Display0
	};*/
	class CameraController;
	class Camera 
	{
	public:
		Camera() = default;
		Camera(float FOV, float Near, float Far, float aspect);
		Camera(float pitch, float yaw, const glm::vec3 & position, float FOV, float Near, float Far, float aspect);
		Camera(float aspectRatio, float scale);
		~Camera() = default;
		void OnImGui();
		const glm::vec3& GetPosition();
		void SetPosition(const glm::vec3 & position);
		void SetMouseSensitivity(float value);
		void SetIsOrthographic(bool ortho);
		bool IsOrthographic()const;
		void SetOrientation(float pitch, float yaw, float roll);
		float GetRoll() const;

		void SetRoll(float y);

		float GetYaw() const;
		void SetYaw(float y);

		float GetPitch() const;
		void SetPitch(float p);

		float GetAspectRatio() const;
		void SetAspectRatio(float y);

		const glm::mat4& GetProjectionMatrix();
		const glm::mat4& GetViewMatrix();

		glm::quat GetOrientation() const;

		float GetFar() const;
		float GetNear() const;

		void SetFar(float pFar);
		void SetNear(float pNear);
		float GetFOV() const;

		float GetScale() const;
		void SetScale(float scale);
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;

		void SetCameraController(const Ref<CameraController> & controller);
		const Ref<CameraController>& GetController() const;

		void SetCameraControllerType(ControllerType type);

		template<typename Archive>
		void save(Archive& archive) const
		{
			archive(cereal::make_nvp("Scale", m_Scale), cereal::make_nvp("Aspect", m_AspectRatio), cereal::make_nvp("FOV", m_Fov), cereal::make_nvp("Near", m_Near), cereal::make_nvp("Far", m_Far));
		}

		template<typename Archive>
		void load(Archive& archive)
		{
			archive(cereal::make_nvp("Scale", m_Scale), cereal::make_nvp("Aspect", m_AspectRatio), cereal::make_nvp("FOV", m_Fov), cereal::make_nvp("Near", m_Near), cereal::make_nvp("Far", m_Far));

			m_ViewDirty = true;
			m_ProjectionDirty = true;
		}


	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
		float m_Pitch;
		float m_Yaw;
		float m_Roll;

		glm::vec3 m_Position=glm::vec3(0.0f);

		float m_AspectRatio;
		float m_Scale = 1.0f;
		float m_Zoom = 1.0f;

		glm::vec2 m_ProjectionOffset = glm::vec2(0.0f, 0.0f);

		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;

		bool m_ProjectionDirty = false;
		bool m_ViewDirty = false;
		bool customProjection_ = false;

		float m_Fov, m_Near, m_Far;
		float m_MouseSensitivity = 0.1f;

		uint32_t m_ScreenWidth;
		uint32_t m_ScreenHeight;

		bool m_Orthographic = false;

		ControllerType m_ControllerType = ControllerType::EditorCamera;
		Ref<CameraController> m_CameraController;

	
	};
}