////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Transform.h"

// Constructor
Transform::Transform()
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "Transform()");

  this->position = glm::vec3(0);
  this->rotation = glm::quat(1, 0, 0, 0);
  this->scale = glm::vec3(1);
  this->parent = nullptr;

  this->Update();
}

// Destructor
Transform::~Transform()
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "~Transform()");
}

// Translate function
void Transform::Translate(const glm::vec3& value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void Translate(const glm::vec3& value)");

  this->SetDirty(true);
  this->position += value;
}

// Rotate function
void Transform::Rotate(const glm::vec3& value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void Rotate(const glm::vec3& value)");

  this->SetDirty(true);
  this->rotation = glm::rotate(this->rotation, glm::radians(value.x), glm::vec3(1, 0, 0));
  this->rotation = glm::rotate(this->rotation, glm::radians(value.y), glm::vec3(0, 1, 0));
  this->rotation = glm::rotate(this->rotation, glm::radians(value.z), glm::vec3(0, 0, 1));
}

// Update transform
void Transform::Update()
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void Update()");

  this->matrix = glm::translate(glm::mat4(1), this->position);
  this->matrix *= glm::toMat4(this->rotation);
  this->matrix = glm::scale(this->matrix, this->scale);

  if (this->parent)
  {
    this->matrix = this->parent->GetMatrix() * this->matrix;
  }

  this->SetDirty(false);
}

// Set position
void Transform::SetPosition(const glm::vec3& value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void SetPosition(const glm::vec3& value)");

  this->position = value;
}

// Set scale
void Transform::SetScale(const glm::vec3& value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void SetScale(const glm::vec3& value)");

  this->scale = value;
}

// Set rotation
void Transform::SetRotation(const glm::vec3& value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void SetRotation(const glm::vec3& value)");

  this->rotation = glm::quat(value);
}

// Set transform dirty
void Transform::SetDirty(const bool &value)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void SetDirty(const bool &value)");

  this->isDirty = value;
}

// Set parent transform
void Transform::SetParent(Transform* parent)
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "void SetParent(Transform* parent)");

  this->parent = parent;
}

// Get position
glm::vec3 Transform::GetPosition() const
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "glm::vec3 GetPosition() const");

  return this->position;
}

// Get scale
glm::vec3 Transform::GetScale() const
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "glm::vec3 GetScale() const");

  return this->scale;
}

// Get rotation
glm::quat Transform::GetRotation() const
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "glm::quat GetRotation() const");

  return this->rotation;
}

// Get transform matrix
glm::mat4 Transform::GetMatrix()
{
  Logger::LogTrace(Logger::Module::TRANSFORM, "glm::mat4 GetMatrix()");

  this->Update();
  return this->matrix;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
