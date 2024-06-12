////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <cfloat>
#include <glm/glm.hpp>
#include "../core/Input.h"
#include "../gl/Camera.h"
#include "../manager/BlockManager.h"
#include "../view/Renderer.h"
#include "../world/World.h"

// Raycast class
class Raycast
{
  // Ray
  public:
    struct Ray
    {
      BlockManager::Value hitValue;
      BlockManager::Value neighborValue;
      glm::vec3 hitPosition;
      glm::vec3 neighborPosition;
      bool isHit;

      Ray(BlockManager::Value hitValue, const glm::vec3 &hitPosition, BlockManager::Value neighborValue, const glm::vec3 &neighborPosition, bool isHit)
      {
        this->hitValue = hitValue;
        this->neighborValue = neighborValue;
        this->hitPosition = hitPosition;
        this->neighborPosition = neighborPosition;
        this->isHit = isHit;
      }
    };

  // Methods
  public:
    static Raycast::Ray CastFromCamera(const float &distance, Camera &camera);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
