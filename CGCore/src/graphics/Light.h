#pragma once
#include"glm/glm.hpp"
namespace CGCore {
	enum class LightType {
		DirectionalLight=0,
		PointLight,
		SpotLight
	};
	struct Light
	{
		Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec4& color=glm::vec4(1.0f) ):m_Color(color),m_Position(position),m_Direction(direction) {}
		glm::vec4 m_Color;
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
	};


}