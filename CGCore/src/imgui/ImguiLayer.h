#pragma once
#include"base/Base.h"
#include"base/Layer.h"
#include"imgui.h"
namespace CGCore {
	class ImguiLayer:public Layer
	{
	public:
		ImguiLayer() :Layer("ImguiLayer") {}
		virtual ~ImguiLayer() {};
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();
	private:
		bool m_ShowDemo = true;

	};
}

