#include"pch.h"
#include "Scene.h"
#include "Entity.h"
#include"Component.h"
namespace CGCore {
	void Scene::OnUpdate(float deltaTime)
	{
	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		auto tagName = name.empty() ? "Unamed Entity" : name;
		entity.AddComponent<TagComponent>(tagName);
		return entity;
	}
}