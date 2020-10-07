#pragma once
#include"base/Base.h"
#include"entt/entt.hpp"
namespace CGCore {
	class Entity;
	class Scene
	{
	public:
		Scene() {};
		~Scene() {};

		void OnUpdate(float deltaTime);

		Entity CreateEntity(const std::string& name = std::string());

		void DistroyEntity(Entity entity);

		entt::registry& GetRegistry() { return m_Registry; }

		const entt::registry& GetRegistry() const { return m_Registry; }

		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		entt::registry m_Registry;
		friend class Entity;
	};
	
}

