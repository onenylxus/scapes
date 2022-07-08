////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Camera3D.h"

// Constructor
Camera3D::Camera3D(const glm::vec3 &position, const float &fov, const float &near, const float &far) : Camera(position, fov, near, far)
{

}

// Create projection matrix
glm::mat4 Camera3D::CreateProjection() const
{
  glm::vec2 size = Engine::GetWindowSize();
  float aspect = size.y == 0 ? 0.0f : size.x / size.y;
  return glm::perspective(fov, aspect, near, far);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////