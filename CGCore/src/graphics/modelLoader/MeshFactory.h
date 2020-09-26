#pragma once
#include "base/Base.h"
#include "glm/glm.hpp"

namespace CGCore {
	enum class PrimitiveType
	{
		Plane,
		Quad,
		Cube,
		Pyramid,
		Sphere,
		Capsule,
		Cylinder
	};
	class Mesh;
	class MeshFactory
	{
	public:
		static Ref<Mesh> CreateQuad();
		static Ref<Mesh> CreateQuad(float x, float y, float width, float height);
		static Ref<Mesh> CreatePlane(float width, float height, const glm::vec3& normal);

	};

}

