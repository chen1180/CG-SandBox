#include "pch.h"
#include "ImguiHelper.h"

namespace CGCore {
	bool ImGuiHelpers::Property(const std::string& name, bool& value)
	{
		bool updated = false;
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if (ImGui::Checkbox(id.c_str(), &value))
			updated = true;

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return updated;
	}

	bool ImGuiHelpers::Property(const std::string& name, float& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		bool updated = false;

		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if (ImGui::SliderFloat(id.c_str(), &value, min, max))
			updated = true;

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return updated;
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec2& value, ImGuiHelpers::PropertyFlag flags)
	{
		return ImGuiHelpers::Property(name, value, -1.0f, 1.0f, flags);
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec2& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		bool updated = false;

		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if (ImGui::SliderFloat2(id.c_str(),glm::value_ptr(value), min, max))
			updated = true;

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return updated;
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec3& value, ImGuiHelpers::PropertyFlag flags)
	{
		return ImGuiHelpers::Property(name, value, -1.0f, 1.0f, flags);
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec3& value, float min, float max, ImGuiHelpers::PropertyFlag flags)
	{
		bool updated = false;

		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
		{
			if (ImGui::ColorEdit3(id.c_str(),glm::value_ptr(value), ImGuiColorEditFlags_NoInputs))
				updated = true;
		}
		else
		{
			if (ImGui::SliderFloat3(id.c_str(),glm::value_ptr(value), min, max))
				updated = true;
		}

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return updated;
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec4& value, bool exposeW, ImGuiHelpers::PropertyFlag flags)
	{
		return Property(name, value, -1.0f, 1.0f, exposeW, flags);
	}

	bool ImGuiHelpers::Property(const std::string& name,glm::vec4& value, float min, float max, bool exposeW, ImGuiHelpers::PropertyFlag flags)
	{
		bool updated = false;

		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
		{
			if (ImGui::ColorEdit4(id.c_str(),glm::value_ptr(value), ImGuiColorEditFlags_NoInputs))
				updated = true;
		}
		else if ((exposeW ? ImGui::SliderFloat4(id.c_str(),glm::value_ptr(value), min, max) : ImGui::SliderFloat3(id.c_str(),glm::value_ptr(value), min, max)))
			updated = true;

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return updated;
	}

}