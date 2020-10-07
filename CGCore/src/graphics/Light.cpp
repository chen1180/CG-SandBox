#include "pch.h"
#include "base/Log.h"
#include "Light.h"
#include <imgui.h>
#include "glm/gtc/type_ptr.hpp"
#include "imgui/ImguiHelper.h"

namespace CGCore {
	std::string Light::LightTypeToString(LightType type)
	{
		switch (type)
		{
		case LightType::DirectionalLight:
			return "Directional Light";
		case LightType::SpotLight:
			return "Spot Light";
		case LightType::PointLight:
			return "Point Light";
		default:
			return "ERROR";
		}
	}

	float Light::StringToLightType(const std::string& type)
	{
		if (type == "Directional")
			return float(LightType::DirectionalLight);

		if (type == "Point")
			return float(LightType::PointLight);

		if (type == "Spot")
			return float(LightType::SpotLight);

		CG_CORE_ERROR("Unknown Light Type");
		return 0.0f;
	}

	void Light::OnImGui()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
		ImGui::Columns(2);
		ImGui::Separator();
		
		if (Type != 0)
			ImGuiHelpers::Property("Position", Position,-50.0,50.0);
		if (Type != 1)
			ImGuiHelpers::Property("Direction", Direction);
		if (Type != 0)
			ImGuiHelpers::Property("Radius", Radius, 0.0f, 100.0f);

		ImGuiHelpers::Property("Colour", Color,true, ImGuiHelpers::PropertyFlag::ColorProperty);
		ImGuiHelpers::Property("Intensity", Intensity, 0.0f, 100.0f);
		
		if (Type == 2)
			ImGuiHelpers::Property("Angle", Angle, 0.0,90.0f);

		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted("Light Type");
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		if (ImGui::BeginMenu(LightTypeToString(LightType(float(Type))).c_str()))
		{
			if (ImGui::MenuItem("Directional Light", "", static_cast<int>(Type) == 0, true))
			{
				Type = float(int(LightType::DirectionalLight));
			}
			if (ImGui::MenuItem("Point Light", "", static_cast<int>(Type) == 1, true))
			{
				Type = float(int(LightType::PointLight));
			}
			if (ImGui::MenuItem("Spot Light", "", static_cast<int>(Type) == 2, true))
			{
				Type = float(int(LightType::SpotLight));
			}
			ImGui::EndMenu();
		}

		ImGui::PopItemWidth();
		ImGui::NextColumn();
		
		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::PopStyleVar();
	}
}
