////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../gl/Object.h"

// Prototypes
class EntityManager;
class World;

// Entity class
class Entity
{
  public:
    friend class EntityManager;

  // Constructor and destructor
  public:
    Entity(const glm::vec3& position);
    virtual ~Entity();

  // Properties
  private:
    Object* object;
    glm::vec3 size;
    glm::vec3 velocity;
    glm::vec3 direction;
    float speed;
    bool isPhysicsEnabled;
    bool isHovering;

  // Methods
  public:
    void Translate(const glm::vec3& position);
    void ApplyDirection(const glm::vec3& direction);
    void ApplyVelocity(const glm::vec3& velocity);

  protected:
    void Move();
    virtual void OnUpdate();
    virtual void OnRender(Camera& camera);
    virtual void OnCollision(const glm::vec3& normal);

  // Setters
  public:
    void SetPosition(const glm::vec3& position);
    void SetDirection(const glm::vec3& direction);
    void SetPhysics(const bool& state);
    void SetSpeed(const float& speed);
    void SetHovering(const bool& hovering);

  // Getters
  public:
    bool IsHovering() const;
    glm::vec3 GetPosition() const;
    glm::mat4 GetMatrix() const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
