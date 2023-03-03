////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AABB.h"

// Camera class
class Camera
{
  // Frustum
  public:
    enum class Frustum
    {
      LEFT,
      RIGHT,
      TOP,
      BOTTOM,
      NEAR,
      FAR
    };

  // Constructor and destructor
  public:
    Camera(const glm::vec3 &position, const float &fov, const float &near, const float &far);
    virtual ~Camera();

  // Properties
  protected:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 top;
    float fov;
    float near;
    float far;
    float yaw;
    float pitch;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec4 frustum[6];
    bool isDirty;

  // Methods
  public:
    void MoveBy(const glm::vec3 &position);
    void RotateBy(const float &yaw, const float &pitch);

  protected:
    virtual void UpdateCamera();
    virtual glm::mat4 CreateProjection() const = 0;
    void UpdateFrustum();

  // Setters
  public:
    void SetFOV(const float &value);
    void SetNear(const float &value);
    void SetFar(const float &value);
    void SetDirty(const bool &value);

  // Getters
  public:
    bool IsPointInFrustum(const glm::vec3 &point);
    bool IsAABBInFrustum(const AABB &aabb);
    glm::vec3 GetPosition() const;
    glm::vec3 GetFront();
    glm::vec3 GetRight();
    glm::vec3 GetTop();
    float GetNear() const;
    float GetFar() const;
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    glm::mat4 GetProjectionView();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
