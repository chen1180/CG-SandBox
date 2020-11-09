#pragma once
#include "base/Base.h"
#include "base/Log.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"
namespace CGCore
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene> & scene);

		void SetContext(const Ref<Scene> & scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

	template<typename T, typename UIFunction>
	static void AddUIComponent(const std::string& name, Entity entity, UIFunction uiFunction);


}

