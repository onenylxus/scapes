////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../core/Input.h"
#include "../world/Entity.h"
#include "Camera3D.h"

// Player camera class
class CameraPlayer : public Camera3D
{
  // Constructor and destructor
  public:
    CameraPlayer(Entity& entity, const glm::vec3& position);
    virtual ~CameraPlayer();

  // Properties
  private:
    Entity* entity;

  // Methods
  public:
    void Update();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
