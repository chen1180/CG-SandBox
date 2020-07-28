#pragma once
#include<string>
namespace CGCore {
	class Layer
	{
	public:
		Layer(const std::string& name) :m_DebugName(name) {}
		virtual ~Layer() {};
		virtual void OnUpdate()=0;
		virtual void OnImGuiRender() = 0;
		virtual void OnAttach()=0;
		virtual void OnDettach() = 0;
		inline std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};
}


