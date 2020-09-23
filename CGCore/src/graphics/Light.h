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
		Light(const glm::vec4& position, const glm::vec3& direction, const glm::vec4& color=glm::vec4(1.0f) ):Color(color), Position(position) {}
		glm::vec4 Position;
		glm::vec4 Color;

	};


}