#pragma once
#include"base/Base.h"
#include<entt/entt.hpp>

namespace CGCore {
	class Entity;
	class Scene
	{
	public:
		Scene(const std::string& sceneName="Untitled scene"):m_SceneName(sceneName) {};
		~Scene() {};

		void OnUpdate(float deltaTime);

		Entity CreateEntity(const std::string& name = std::string());

		void DistroyEntity(Entity entity);

		void DistroyAllEntities();

		entt::registry& GetRegistry() { return m_Registry; }

		const entt::registry& GetRegistry() const { return m_Registry; }

		void OnViewportResize(uint32_t width, uint32_t height);

		virtual void Serialise(const std::string& filePath, bool binary = false);
		virtual void Deserialise(const std::string& filePath, bool binary = false);

		template<typename Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::make_nvp("Scene Name", m_SceneName));
		
		}

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		std::string m_SceneName;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		entt::registry m_Registry;
		friend class Entity;
	};
	
}

