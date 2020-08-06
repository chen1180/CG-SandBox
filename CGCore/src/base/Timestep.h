#pragma once
namespace CGCore {
	class TimeStep {
	public:
		TimeStep():m_LastTime(0.0f), m_DeltaTime(0.0f){}
		
		float UpdateDeltaTime(float currentTime) {
			m_DeltaTime = currentTime - m_LastTime;
			m_LastTime = currentTime;
			return m_DeltaTime;
		}
		operator float() { return m_DeltaTime; }
	private:
		float m_LastTime;
		float m_DeltaTime;
	};
}