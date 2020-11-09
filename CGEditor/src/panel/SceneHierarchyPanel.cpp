#include "SceneHierarchyPanel.h"
#include "imgui.h"
#include"imgui_internal.h"
#include <glm/gtc/type_ptr.hpp>
#include "ECS/Component.h"
namespace CGCore
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->GetRegistry().each([&](auto entityID)
		{
			Entity entity{ entityID , m_Context.get() };
			DrawEntityNode(entity);
		});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		if (ImGui::BeginPopupContextWindow(0,1,false))
		{
			if(ImGui::MenuItem("Create entity"))
				m_Context->CreateEntity("Empty entity");
			if (ImGui::MenuItem("Remove all entities"))
				m_Context->DistroyAllEntities();
			ImGui::EndPopup();
		}
		
		ImGui::End();

		ImGui::Begin("Properties");
		
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		
		}
		
		ImGui::End();
	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete entity"))
				entityDeleted = true;
			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
		
		if(entityDeleted)
		{
			m_Context->DistroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}

	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("+"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Light"))
			{
				m_SelectionContext.AddComponent<Light>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Camera"))
			{
				Ref<Camera> m_Camera = CreateRef<Camera>(60.0f, 0.1f, 100.0f, 1.3);
				m_SelectionContext.AddComponent<CameraComponent>(m_Camera);
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("SpriteRenderer"))
			{
				m_SelectionContext.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Model"))
			{
				m_SelectionContext.AddComponent<Model>("assets/mesh/sphere.obj");
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();


		AddUIComponent<TransformComponent>("Transform", entity, [](auto& component)
		{
			component.OnImGui();
		});

		AddUIComponent<CameraComponent>("Camera", entity, [](auto& component)
		{
			component.Cam->OnImGui();
			ImGui::Checkbox("Is Primary", &component.IsMainCamera);
		});

		AddUIComponent<Light>("Light", entity, [](auto& component)
		{
			component.OnImGui();
		});

		AddUIComponent<Model>("MeshRenderer", entity, [](auto& component)
		{
			//TODO: add file dialog in the future
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::Columns(2);
			ImGui::Separator();

			ImGui::AlignTextToFramePadding();
			ImGui::Text("Resources");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), component.GetFilePath().c_str());
			if (ImGui::InputText("##Resources", buffer, sizeof(buffer)))
			{
				component.SavePathAndLoadModel( std::string(buffer));
				
			}
			ImGui::PopItemWidth();
			ImGui::NextColumn();

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::PopStyleVar();
		});
			
		AddUIComponent<SpriteRendererComponent>("SpriteRenderer", entity, [](auto& component)
		{
			auto& color = component.Color;
			ImGui::ColorEdit4("Color", glm::value_ptr(color));
		});
	}

	template<typename T, typename UIFunction>
	void AddUIComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed| ImGuiTreeNodeFlags_SpanAvailWidth| ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x-lineHeight*0.5f);

			if (ImGui::Button("..", ImVec2{lineHeight,lineHeight}))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();

		}
	}

}