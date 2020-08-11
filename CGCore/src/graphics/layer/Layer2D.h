#pragma once
#include "Layer.h"
namespace CGCore {
	class Layer2D :
		public Layer
	{
	public:
		Layer2D();
		~Layer2D();
		virtual void OnUpdate(float deltaTime)override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach()override;
		virtual void OnDettach()override;
		virtual void OnEvent(Event& e) override;
	private:
	};

}


