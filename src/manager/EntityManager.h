////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <vector>
#include "../gl/Camera.h"

// Prototypes
class Entity;

// Entity manager class
class EntityManager
{
// Friend class
public:
  friend class Entity;

// Properties
private:
  static std::vector<Entity *> entities;

// Methods
public:
  static void Update();
  static void Render(Camera &camera);

private:
  static void Add(Entity &entity);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
