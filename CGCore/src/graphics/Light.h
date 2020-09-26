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
		Light() = default;
		Light(const glm::vec4& position, const glm::vec4& direction, const glm::vec4& color=glm::vec4(1.0f) ):Color(color), Position(position),Direction(direction) {}
		glm::vec4 Position;
		glm::vec4 Direction;
		glm::vec4 Color;


	};


}