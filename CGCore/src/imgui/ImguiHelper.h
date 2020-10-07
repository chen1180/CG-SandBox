#pragma once
#include"base/Base.h"
#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include <imgui.h>
#include <imgui_internal.h>
namespace CGCore {
	namespace ImGuiHelpers
	{
		enum class PropertyFlag
		{
			None = 0, ColorProperty = 1
		};

		bool Property(const std::string& name, bool& value);
		bool Property(const std::string& name, float& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
		bool Property(const std::string& name, glm::vec2& value, PropertyFlag flags);
		bool Property(const std::string& name, glm::vec2& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
		bool Property(const std::string& name, glm::vec3& value, PropertyFlag flags);
		bool Property(const std::string& name, glm::vec3& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
		bool Property(const std::string& name, glm::vec4& value, bool exposeW, PropertyFlag flags);
		bool Property(const std::string& name, glm::vec4& value, float min = -1.0f, float max = 1.0f, bool exposeW = false, PropertyFlag flags = PropertyFlag::None);


	}

}