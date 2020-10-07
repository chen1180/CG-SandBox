#include "SceneHierarchyPanel.h"
#include "imgui.h"
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
			ImGui::EndPopup();
		}
		
		ImGui::End();

		ImGui::Begin("Properties");
		
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);

			if (ImGui::Button("Add component"))
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
					Ref<Camera> m_Camera = CreateRef<Camera>(60.0f, 0.1f, 100.0f,1.3);
					m_SelectionContext.AddComponent<CameraComponent>(m_Camera);
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("SpriteRenderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Mesh"))
				{
					m_SelectionContext.AddComponent<MeshComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

		}
		
		ImGui::End();
	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
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
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), flags, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				transform.OnImGui();

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), flags, "Camera");
			ImGui::SameLine();
			
			if (ImGui::Button("+")) 
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
				auto& cameraComponent = entity.GetComponent<CameraComponent>();

				cameraComponent.Cam->OnImGui();
				ImGui::Checkbox("Is Primary", &cameraComponent.IsMainCamera);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<CameraComponent>();
		}

		if(entity.HasComponent<Light>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(Light).hash_code(), flags, "Light");
			ImGui::SameLine();

			if (ImGui::Button("+"))
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
				auto& lightComponent = entity.GetComponent<Light>();
				lightComponent.OnImGui();

				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<Light>();
			
		}

		if (entity.HasComponent<MeshComponent>())
		{

			bool open = ImGui::TreeNodeEx((void*)typeid(MeshComponent).hash_code(), flags, "MeshRenderer");
			ImGui::SameLine();

			if (ImGui::Button("+"))
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
				auto& mesh = entity.GetComponent<MeshComponent>();
				ImGui::Text("Meshes");

				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<MeshComponent>();


		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), flags, "SpriteRenderer");
			ImGui::SameLine();

			if (ImGui::Button("+"))
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
				auto& lightComponent = entity.GetComponent<SpriteRendererComponent>();
				auto& color = lightComponent.Color;
				ImGui::ColorEdit4("Color", glm::value_ptr(color));
				
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<SpriteRendererComponent>();


		}
	}

}