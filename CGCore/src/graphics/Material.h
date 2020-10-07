#pragma once
namespace CGCore {
	class Material
	{
	public:
		Material() = default;
		Material(float metallic, float roughness, float ao = 0.1f) :Metallic(metallic), Roughness(roughness), Ao(ao) {}
		float Metallic = 0.0f;
		float Roughness = 0.0f;
		float Ao = 0.0f;
	};

}
