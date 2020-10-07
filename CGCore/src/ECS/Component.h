#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/quaternion.hpp"
#include"glm/gtx/quaternion.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"pch.h"

#include "imgui.h"
#include"graphics/modelLoader/Mesh.h"
#include"graphics/camera/Camera.h"
#include "graphics/Light.h"
#include"graphics/Material.h"
#include"entt/entt.hpp"
namespace CGCore {
	struct TagComponent {
		std::string Tag{ "" };

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};
	struct MeshComponent {
		Ref<Mesh> Meshes = nullptr;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const Ref<Mesh>& mesh)
			: Meshes(mesh) {}

	};
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4 & color)
			: Color(color) {}
	};
	struct CameraComponent {
		Ref<Camera> Cam;
		bool IsMainCamera=false;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const Ref<Camera>& cam,bool isMainCamera=false)
			: Cam(cam),IsMainCamera(IsMainCamera) {}

	};
	class TransformComponent {
	public:
		TransformComponent() = default;
		TransformComponent(const glm::vec3& position) :m_LocalPosition(position) {
			m_LocalMatrix = glm::translate(glm::mat4(1.0f), m_LocalPosition) * glm::toMat4(m_LocalOrientation) * glm::scale(glm::mat4(1.0f),m_LocalScale);
		}
		const glm::vec3& GetWorldPosition() { 
			return glm::vec3(m_WorldMatrix[3]); 
		}
		const glm::quat& GetWorldOrientation() {
			return  glm::quat_cast(m_WorldMatrix);
		}
		const glm::vec3& GetWorldScale() {
			glm::vec3 scale;
			glm::quat rotation;
			glm::vec3 translation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(m_WorldMatrix, scale, rotation, translation, skew, perspective);

			return scale;
		}
		const glm::vec3& GetLocalPosition() {
			return m_LocalPosition;
		}
		const glm::quat& GetLocalOrientation() {
			return m_LocalOrientation;
		}
		const glm::vec3& GetLocalScale() {
			return m_LocalScale;
		}
		glm::mat4& GetWorldMatrix()
		{
			if (m_Dirty)
				UpdateMatrix();

			return m_WorldMatrix;
		}

		const  glm::mat4& GetLocalMatrix()
		{
			if (m_Dirty)
				UpdateMatrix();

			return m_LocalMatrix;
		}

		void SetLocalPosition(const glm::vec3& position) {
			m_Dirty = true;
			m_LocalPosition = position;
		}
		void SetLocalScale(const glm::vec3& newScale)
		{
			m_Dirty = true;
			m_LocalScale = newScale;
		}

		void SetLocalOrientation(const glm::quat& quat)
		{
			m_Dirty = true;
			m_LocalOrientation = quat;
		}
		void SetLocalTransform(const glm::mat4& localMat)
		{
			m_LocalMatrix = localMat;
			m_HasUpdated = true;

			ApplyTransform();
		}
		void SetWorldMatrix(const glm::mat4& mat)
		{
			if (m_Dirty)
				UpdateMatrix();
			m_WorldMatrix = mat * m_LocalMatrix;
		}

		void OnImGui()
		{
			auto rotation = glm::eulerAngles(m_LocalOrientation) ;

			bool update = false;

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::Columns(2);
			ImGui::Separator();

			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Position");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			if (ImGui::DragFloat3("##Position",glm::value_ptr(m_LocalPosition)),.01f)
			{
				update = true;
			}

			ImGui::PopItemWidth();
			ImGui::NextColumn();

			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Rotation");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			if (ImGui::DragFloat3("##Rotation", glm::value_ptr(rotation)),0.01f)
			{
				float pitch = glm::min(rotation.x, glm::radians(89.9f));
				pitch = glm::max(pitch, glm::radians(-89.9f));
				SetLocalOrientation(glm::quat(glm::vec3(pitch, rotation.y, rotation.z)));
				update = true;
			}

			ImGui::PopItemWidth();
			ImGui::NextColumn();

			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Scale");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			if (ImGui::DragFloat3("##Scale", glm::value_ptr(m_LocalScale), 0.1f))
			{
				update = true;
			}

			ImGui::PopItemWidth();
			ImGui::NextColumn();

			if (update)
				UpdateMatrix();

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::PopStyleVar();
			
		}


	private:
		void UpdateMatrix() {
			m_LocalMatrix = glm::translate(glm::mat4(1.0f), m_LocalPosition) * glm::toMat4(m_LocalOrientation) * glm::scale(glm::mat4(1.0f), m_LocalScale);
			m_Dirty = false;
			m_HasUpdated = true;
		}
		void ApplyTransform()
		{
			m_LocalPosition = glm::vec3(m_LocalMatrix[3]);
			m_LocalOrientation = glm::quat_cast(m_LocalMatrix);
			m_LocalScale = glm::vec3(m_LocalMatrix[0][0], m_LocalMatrix[1][1], m_LocalMatrix[2][2]);
		}
		glm::mat4	m_LocalMatrix = glm::mat4(1.0f);
		glm::mat4	m_WorldMatrix = glm::mat4(1.0f);

		glm::vec3	m_LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3	m_LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::quat	m_LocalOrientation = glm::identity<glm::quat>();



		bool m_Dirty=false;
		bool m_HasUpdated = true;

	};
	class Hierarchy
	{
	public:
		Hierarchy(entt::entity p = entt::null) : _parent{ p } {}

		inline entt::entity parent() const { return _parent; }
		inline entt::entity next() const { return _next; }
		inline entt::entity prev() const { return _prev; }
		inline entt::entity first() const { return _first; }

		// Return true if rhs is an ancestor of rhs
		bool compare(const entt::registry& registry, const entt::entity rhs) const;

		// update hierarchy components when hierarchy component is added
		static void on_construct(entt::registry& registry, entt::entity entity);

		// update hierarchy components when hierarchy component is removed
		static void on_destroy(entt::registry& registry, entt::entity entity);

		static void on_update(entt::registry& registry, entt::entity entity);

		static void Reparent(entt::entity entity, entt::entity parent, entt::registry& registry, Hierarchy& hierarchy);

		entt::entity _parent = entt::null;
		entt::entity _first = entt::null;
		entt::entity _next = entt::null;
		entt::entity _prev = entt::null;
	};
}