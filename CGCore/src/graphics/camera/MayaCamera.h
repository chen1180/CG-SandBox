#pragma once
#include "CameraController.h"
namespace CGCore {
	class MayaCameraController :
		public CameraController
	{
	public:
		MayaCameraController();
		virtual ~MayaCameraController() override;

		virtual void HandleMouse(Camera* camera, float dt, float xpos, float ypos) override;
		virtual void HandleKeyboard(Camera* camera, float dt) override;

		void MousePan(Camera* camera, const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta, const float dt);
		void MouseZoom(float delta, const float dt);
		glm::vec3 CalculatePosition(Camera* camera) const;

	private:


		float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;
		bool m_Free;
	};
}

