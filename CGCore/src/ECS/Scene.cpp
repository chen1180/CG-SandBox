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
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DistroyEntity(Entity entity)
	{
		 m_Registry.destroy(entity); 
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportHeight = height;
		m_ViewportWidth = width;
		//Resize camera 
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			cameraComponent.Cam->SetAspectRatio(float(m_ViewportWidth) / m_ViewportHeight);

		}
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}
	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
		
	}
	template<>
	void Scene::OnComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Cam->SetAspectRatio(float(m_ViewportWidth) / m_ViewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<Light>(Entity entity, Light& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<Material>(Entity entity, Material& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<Hierarchy>(Entity entity, Hierarchy& component)
	{

	}
}
