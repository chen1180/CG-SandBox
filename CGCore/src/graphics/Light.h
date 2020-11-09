#pragma once
#include"math/Math.h"

namespace CGCore {
	enum class LightType {
		DirectionalLight=0,
		PointLight,
		SpotLight
	};
	struct Light
	{
	public:
		Light() = default;
		Light(const glm::vec4& position, 
			const glm::vec4& direction, 
			const glm::vec4& color = glm::vec4(1.0f), 
			const LightType& type = LightType::DirectionalLight, 
			float intensity = 1.0f,
			float radius=100.0f,
			float angle=60.0f):Color(color), Position(position), Direction(direction), Type(float(type)),Intensity(intensity),Radius(radius),Angle(angle){}

		std::string Light::LightTypeToString(LightType type);

		float Light::StringToLightType(const std::string& type);

		void OnImGui();

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(Position), CEREAL_NVP(Direction), CEREAL_NVP(Color), CEREAL_NVP(Type), CEREAL_NVP(Intensity), CEREAL_NVP(Radius), CEREAL_NVP(Angle));
		}

	public:
		glm::vec4 Position;
		glm::vec4 Direction;
		glm::vec4 Color;
		float Type;
		float Intensity;
		float Radius;
		float Angle;


	};


}