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
		entt::registry& GetRegistry() { return m_Registry; }
		const entt::registry& GetRegistry() const { return m_Registry; }
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}

