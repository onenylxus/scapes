////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#include "../world/Entity.h"
#include "EntityManager.h"

// Set default values
std::vector<Entity *> EntityManager::entities;

// Update entities
void EntityManager::Update()
{
	Logger::LogTrace(ModuleData::Name::ENTITY_MANAGER, "void Update()");

	for (int i = 0; i < EntityManager::entities.size(); i++)
	{
		EntityManager::entities[i]->OnUpdate();
	}
}

// Render entities
void EntityManager::Render(Camera &camera)
{
	Logger::LogTrace(ModuleData::Name::ENTITY_MANAGER, "void Render(Camera &camera)");

	for (int i = 0; i < EntityManager::entities.size(); i++)
	{
		EntityManager::entities[i]->OnRender(camera);
	}
}

// Add entity
void EntityManager::Add(Entity &entity)
{
	Logger::LogTrace(ModuleData::Name::ENTITY_MANAGER, "void AddEntity(Entity &entity)");

	EntityManager::entities.push_back(&entity);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
