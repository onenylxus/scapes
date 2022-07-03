////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Camera2D.h"

// Constructor
Camera2D::Camera2D(const glm::vec3 &position, const glm::vec3 &front, const float &left, const float &right, const float &top, const float &bottom) : Camera(position, 60.0f, 0.1f, 1000.0f)
{
  this->front = front;
  this->left = left;
  this->right = right;
  this->top = top;
  this->bottom = bottom;
}

// Update camera
void Camera2D::UpdateCamera()
{
  this->view = glm::lookAt(this->position, this->position + this->front, this->up);
  this->projection = this->CreateProjection();
}

// Create projection matrix
glm::mat4 Camera2D::CreateProjection() const
{
  return glm::ortho(this->left, this->right, this->bottom, this->top, this->near, this->far);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
