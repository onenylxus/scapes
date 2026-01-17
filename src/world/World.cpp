////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "World.h"

// Constructor
World::World()
{
	Logger::LogTrace(ModuleData::Name::WORLD, "World()");

	BlockManager::Init();
	this->skybox = new Skybox("res/skybox/");

	Logger::LogInfo(ModuleData::Name::WORLD, "World created");
}

// Destructor
World::~World()
{
	Logger::LogTrace(ModuleData::Name::WORLD, "~World()");

	delete this->skybox;
	BlockManager::Destroy();

	Logger::LogInfo(ModuleData::Name::WORLD, "World deleted");
}

// Update function
void World::Update()
{
	Logger::LogTrace(ModuleData::Name::WORLD, "void Update()");

	this->skybox->GetShader()->SetFloat("uTime", Clock::GetTotal());
	EntityManager::Update();
}

// Render function
void World::Render()
{
	Logger::LogTrace(ModuleData::Name::WORLD, "void Render()");

	Camera3D *camera = new Camera3D(glm::vec3(0));
	this->skybox->Render(*camera);
	EntityManager::Render(*camera);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
