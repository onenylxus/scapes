////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "World.h"

// Constructor
World::World()
{
  Logger::LogTrace(Logger::Module::WORLD, "World()");

  BlockManager::Init();
  this->skybox = new Skybox("res/skybox/");

  Logger::LogInfo(Logger::Module::WORLD, "World created");
}

// Destructor
World::~World()
{
  Logger::LogTrace(Logger::Module::WORLD, "~World()");

  delete this->skybox;
  BlockManager::Destroy();

  Logger::LogInfo(Logger::Module::WORLD, "World deleted");
}

// Update function
void World::Update()
{
  Logger::LogTrace(Logger::Module::WORLD, "void Update()");

  this->skybox->GetShader()->SetFloat("uTime", Clock::GetTotal());
  EntityManager::Update();
}

// Render function
void World::Render()
{
  Logger::LogTrace(Logger::Module::WORLD, "void Render()");

  Camera3D *camera = new Camera3D(glm::vec3(0));
  this->skybox->Render(*camera);
  EntityManager::Render(*camera);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
