#pragma once
#include<string>
#include"event/Event.h"
namespace CGCore {
	class Layer
	{
	public:
		Layer(const std::string& name) :m_DebugName(name) {}
		virtual ~Layer() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		virtual void OnAttach() {};
		virtual void OnDettach() {};
		virtual void OnEvent(Event& e){};
		inline std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
		 
	};
}


