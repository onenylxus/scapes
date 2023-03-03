////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../core/Engine.h"
#include "../gl/Camera.h"

// 3D camera class
class Camera3D : public Camera
{
  // Constructor and destructor
  public:
    Camera3D(const glm::vec3 &position, const float &fov = 60.0f, const float &near = 0.1f, const float &far = 1000.0f);
    virtual ~Camera3D();

  // Methods
  private:
    virtual glm::mat4 CreateProjection() const override;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
