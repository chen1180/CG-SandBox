#pragma once
#include "CameraController.h"
namespace CGCore {
	class EditorCameraController :
		public CameraController
	{
	public:
		EditorCameraController();
		~EditorCameraController();

		virtual void HandleMouse(Camera* camera, float dt, float xpos, float ypos) override;
		virtual void HandleKeyboard(Camera* camera, float dt) override;

		void UpdateScroll(Camera* camera, float offset, float dt) override;
	};
}

