#include"pch.h"
#include "Scene.h"
#include "Entity.h"
#include"Component.h"

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

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

	void Scene::DistroyAllEntities()
	{
		m_Registry.each([&](auto entity) {
			m_Registry.destroy(entity);
		});
		m_Registry.clear();
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

#define ALL_COMPONENTS TagComponent,SpriteRendererComponent,TransformComponent,Light,CameraComponent,Model,Material
	void Scene::Serialise(const std::string& filePath, bool binary)
	{
		std::string path = filePath;
		path += m_SceneName;
		if (binary)
		{
			path += std::string(".bin");

			std::ofstream file(path, std::ios::binary);

			{
				// output finishes flushing its contents when it goes out of scope
				cereal::BinaryOutputArchive output{ file };
				output(*this);
				entt::snapshot{ m_Registry }.entities(output).component<ALL_COMPONENTS>(output);
			}
			file.close();
		}
		else
		{
			std::stringstream storage;
			path += std::string(".lsn");

			{
				// output finishes flushing its contents when it goes out of scope
				cereal::JSONOutputArchive output{ storage };
				output(*this);
				entt::snapshot{ m_Registry }.entities(output).component<ALL_COMPONENTS>(output);
			}
			std::ofstream myfile(path);
			if (myfile.is_open())
			{
				myfile << storage.str();
				myfile.close();
			}
		}
	}

	void Scene::Deserialise(const std::string& filePath, bool binary)
	{
		//TODO: temporary and remove later, add entity manager
		DistroyAllEntities();

		std::string path = filePath;

		if (binary)
		{

			if (!std::filesystem::exists(path))
			{
				CG_CORE_ERROR("No saved scene file found {0}", path);
				return;
			}

			std::ifstream file(path, std::ios::binary);
			cereal::BinaryInputArchive input(file);
			input(*this);
			entt::snapshot_loader{m_Registry}.entities(input).component<ALL_COMPONENTS>(input); //continuous_loader
		}
		else
		{

			if (!std::filesystem::exists(path))
			{
				CG_CORE_ERROR("No saved scene file found {0}", path);
				return;
			}
			std::ifstream infile(path);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			std::string data = buffer.str();
			std::istringstream istr;
			istr.str(data);
			cereal::JSONInputArchive input(istr);
			input(*this);
			entt::snapshot_loader{ m_Registry }.entities(input).component<ALL_COMPONENTS>(input); //continuous_loader
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
	void Scene::OnComponentAdded<Model>(Entity entity, Model& component)
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
