////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "World.h"

// Constructor
World::World()
{
  this->skybox = new Skybox("res/skybox/");
}

// Destructor
World::~World()
{
  delete this->skybox;
}

// Update function
void World::Update()
{
  this->skybox->GetShader()->SetFloat("uTime", Clock::GetTotal());
}

// Render function
void World::Render()
{
  Camera3D *camera = new Camera3D(glm::vec3(0));
  this->skybox->Render(*camera);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
