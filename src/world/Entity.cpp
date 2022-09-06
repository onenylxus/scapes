////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "../manager/EntityManager.h"
#include "Entity.h"
#include "World.h"

// Constructor
Entity::Entity(const glm::vec3& position)
{
  Logger::LogTrace(Logger::Module::ENTITY, "Entity::Entity(const glm::vec3& position)");

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
  Logger::LogTrace(Logger::Module::ENTITY, "Entity::~Entity()");

  delete this->object;
}

// Direct translate to position
void Entity::Translate(const glm::vec3& position)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::Translate(const glm::vec3& position)");

  this->object->GetTransform()->SetPosition(position);
}

// Apply direction
void Entity::ApplyDirection(const glm::vec3 &direction)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::ApplyDirection(const glm::vec3 &direction)");

  this->direction = glm::normalize(this->direction + direction);
}

// Apply velocity
void Entity::ApplyVelocity(const glm::vec3 &velocity)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::ApplyVelocity(const glm::vec3 &velocity)");

  this->velocity += velocity;
  if (glm::length(this->velocity) > this->speed)
  {
    this->velocity = glm::normalize(this->velocity) * this->speed;
  }
}

// Move by physics
void Entity::Move()
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::Move()");

  this->object->GetTransform()->Translate(this->velocity);
}

// Update event
void Entity::OnUpdate()
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::OnUpdate()");
}

// Render event
void Entity::OnRender(Camera& camera)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::OnRender(Camera& camera)");
}

// Collision event
void Entity::OnCollision(const glm::vec3& normal)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::OnCollision(const glm::vec3& normal)");

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
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::SetPosition(const glm::vec3& position)");

  this->object->GetTransform()->SetPosition(position);
}

// Set direction
void Entity::SetDirection(const glm::vec3& direction)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::SetDirection(const glm::vec3& direction)");

  this->direction = direction;
}

// Set physics
void Entity::SetPhysics(const bool& state)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::SetPhysics(const glm::vec3& physics)");

  this->isPhysicsEnabled = state;
}

// Set speed
void Entity::SetSpeed(const float& speed)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::SetSpeed(const float& speed)");

  this->speed = speed;
}

// Set hovering
void Entity::SetHovering(const bool& hovering)
{
  Logger::LogTrace(Logger::Module::ENTITY, "void Entity::SetHovering(const bool& hovering)");

  this->isHovering = hovering;
}

// Check hovering state
bool Entity::IsHovering() const
{
  Logger::LogTrace(Logger::Module::ENTITY, "bool Entity::IsHovering() const");

  return this->isHovering;
}

// Get position
glm::vec3 Entity::GetPosition() const
{
  Logger::LogTrace(Logger::Module::ENTITY, "glm::vec3& Entity::GetPosition() const");

  return this->object->GetPosition();
}

// Get transform matrix
glm::mat4 Entity::GetMatrix() const
{
  Logger::LogTrace(Logger::Module::ENTITY, "glm::mat4 Entity::GetMatrix() const");

  return this->object->GetTransform()->GetMatrix();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
