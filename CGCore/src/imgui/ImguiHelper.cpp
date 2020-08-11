#include "pch.h"
#include "ImguiHelper.h"

namespace CGCore {
	void ImGuiHelpers::Property(const std::string& name, bool& value)
	{
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::Checkbox(id.c_str(), &value);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void ImGuiHelpers::Property(const std::string& name, float& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::SliderFloat(id.c_str(), &value, min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec2& value, ImGuiHelpers::PropertyFlag flags)
	{
		ImGuiHelpers::Property(name, value, -1.0f, 1.0f, flags);
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec2& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::SliderFloat2(id.c_str(), glm::value_ptr(value), min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec3& value, ImGuiHelpers::PropertyFlag flags)
	{
		ImGuiHelpers::Property(name, value, -1.0f, 1.0f, flags);
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec3& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit3(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat3(id.c_str(), glm::value_ptr(value), min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec4& value, ImGuiHelpers::PropertyFlag flags)
	{
		Property(name, value, -1.0f, 1.0f, flags);
	}

	void ImGuiHelpers::Property(const std::string& name, glm::vec4& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit4(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat4(id.c_str(), glm::value_ptr(value), min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}


}