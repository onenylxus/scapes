////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glm/glm.hpp>

// Axis-aligned bounding box class
class AABB
{
  // Vertices
  public:
    enum class Vertices
    {
      TOP_BACK_LEFT,
      TOP_BACK_RIGHT,
      TOP_FRONT_LEFT,
      TOP_FRONT_RIGHT,
      BOTTOM_BACK_LEFT,
      BOTTOM_BACK_RIGHT,
      BOTTOM_FRONT_LEFT,
      BOTTOM_FRONT_RIGHT
    };

  // Properties
  private:
    glm::vec3 position;
    glm::vec3 vertices[8];
    glm::vec3 min;
    glm::vec3 max;

  // Constructor and destructor
  public:
    AABB(const glm::vec3 &position, const glm::vec3 &size);
    virtual ~AABB() = default;

  // Methods
  public:
    void Update(const glm::vec3 &position, const glm::vec3 &size);

  // Getters
  public:
    static bool IsOverlapping(const glm::vec3 &positionA, const glm::vec3 &sizeA, const glm::vec3 &positionB, const glm::vec3 &sizeB);
    bool IsOverlapping(const glm::vec3 &position, glm::vec3 &size) const;
    bool IsOverlapping(const AABB &aabb) const;
    glm::vec3 GetVertex(const unsigned int &index) const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
