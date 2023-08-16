////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "../manager/EntityManager.h"
#include "Entity.h"
#include "World.h"

// Constructor
Entity::Entity(const glm::vec3& position)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "Entity(const glm::vec3& position)");

  // Set properties
  this->size = glm::vec3(1);
  this->velocity = glm::vec3(0);
  this->direction = glm::vec3(0, 0, 1);
  this->speed = 8.0f;
  this->isPhysicsEnabled = true;
  this->isHovering = true;

  // Create object
  this->object = new Object(position, Mesh::Cube());
  this->object->GetTransform()->SetPosition(position);
  this->object->GetTransform()->SetScale(this->size);

  // Add entity to manager
  EntityManager::Add(*this);
}

// Destructor
Entity::~Entity()
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "~Entity()");

  delete this->object;
}

// Direct translate to position
void Entity::Translate(const glm::vec3& position)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void Translate(const glm::vec3& position)");

  this->object->GetTransform()->SetPosition(position);
}

// Apply direction
void Entity::ApplyDirection(const glm::vec3 &direction)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void ApplyDirection(const glm::vec3 &direction)");

  this->direction = glm::normalize(this->direction + direction);
}

// Apply velocity
void Entity::ApplyVelocity(const glm::vec3 &velocity)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void ApplyVelocity(const glm::vec3 &velocity)");

  this->velocity += velocity;
  if (glm::length(this->velocity) > this->speed)
  {
    this->velocity = glm::normalize(this->velocity) * this->speed;
  }
}

// Move by physics
void Entity::Move()
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void Move()");

  this->object->GetTransform()->Translate(this->velocity);
}

// Update event
void Entity::OnUpdate()
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void OnUpdate()");
}

// Render event
void Entity::OnRender(Camera& camera)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void OnRender(Camera& camera)");
}

// Collision event
void Entity::OnCollision(const glm::vec3& normal)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void OnCollision(const glm::vec3& normal)");

  // Check collision by axes
  if (normal.x > 0.0f)
  {
    this->velocity.x = 0.0f;
  }
  if (normal.y > 0.0f)
  {
    this->velocity.y = 0.0f;
  }
  if (normal.z > 0.0f)
  {
    this->velocity.z = 0.0f;
  }

  // Check hovering state
  this->SetHovering(normal.y == 1.0f);
}

// Set position
void Entity::SetPosition(const glm::vec3& position)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void SetPosition(const glm::vec3& position)");

  this->object->GetTransform()->SetPosition(position);
}

// Set direction
void Entity::SetDirection(const glm::vec3& direction)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void SetDirection(const glm::vec3& direction)");

  this->direction = direction;
}

// Set physics
void Entity::SetPhysics(const bool& state)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void SetPhysics(const glm::vec3& physics)");

  this->isPhysicsEnabled = state;
}

// Set speed
void Entity::SetSpeed(const float& speed)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void SetSpeed(const float& speed)");

  this->speed = speed;
}

// Set hovering
void Entity::SetHovering(const bool& hovering)
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "void SetHovering(const bool& hovering)");

  this->isHovering = hovering;
}

// Check hovering state
bool Entity::IsHovering() const
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "bool IsHovering() const");

  return this->isHovering;
}

// Get position
glm::vec3 Entity::GetPosition() const
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "glm::vec3& GetPosition() const");

  return this->object->GetPosition();
}

// Get transform matrix
glm::mat4 Entity::GetMatrix() const
{
  Logger::LogTrace(ModuleData::Name::ENTITY, "glm::mat4 GetMatrix() const");

  return this->object->GetTransform()->GetMatrix();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
