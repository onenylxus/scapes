////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "AABB.h"

// Constructor
AABB::AABB(const glm::vec3 &position, const glm::vec3 &size)
{
  Logger::LogTrace(Logger::Module::AABB, "AABB(const glm::vec3 &position, const glm::vec3 &size)");

  this->Update(position, size);
}

// Destructor
AABB::~AABB()
{
  Logger::LogTrace(Logger::Module::AABB, "~AABB()");
}

// Update bounding box
void AABB::Update(const glm::vec3 &position, const glm::vec3 &size)
{
  Logger::LogTrace(Logger::Module::AABB, "void Update(const glm::vec3 &position, const glm::vec3 &size)");

  // Set properties
  glm::vec3 half = size / 2.0f;
  this->position = position;
  this->min = position - half;
  this->max = position + half;

  // Set vertices
  this->vertices[(int)AABB::Vertices::TOP_BACK_LEFT] = glm::vec3(min.x, max.y, min.z);
  this->vertices[(int)AABB::Vertices::TOP_BACK_RIGHT] = glm::vec3(max.x, max.y, min.z);
  this->vertices[(int)AABB::Vertices::TOP_FRONT_LEFT] = glm::vec3(min.x, max.y, max.z);
  this->vertices[(int)AABB::Vertices::TOP_FRONT_RIGHT] = glm::vec3(max.x, max.y, max.z);
  this->vertices[(int)AABB::Vertices::BOTTOM_BACK_LEFT] = glm::vec3(min.x, min.y, min.z);
  this->vertices[(int)AABB::Vertices::BOTTOM_BACK_RIGHT] = glm::vec3(max.x, min.y, min.z);
  this->vertices[(int)AABB::Vertices::BOTTOM_FRONT_LEFT] = glm::vec3(min.x, min.y, max.z);
  this->vertices[(int)AABB::Vertices::BOTTOM_FRONT_RIGHT] = glm::vec3(max.x, min.y, max.z);
}

// General overlapping check
bool AABB::IsOverlapping(const glm::vec3 &positionA, const glm::vec3 &sizeA, const glm::vec3 &positionB, const glm::vec3 &sizeB)
{
  Logger::LogTrace(Logger::Module::AABB, "bool IsOverlapping(const glm::vec3 &positionA, const glm::vec3 &sizeA, const glm::vec3 &positionB, const glm::vec3 &sizeB)");

  glm::vec3 halfA = sizeA / 2.0f;
  glm::vec3 minA = positionA - halfA;
  glm::vec3 maxA = positionA + halfA;
  glm::vec3 halfB = sizeB / 2.0f;
  glm::vec3 minB = positionB - halfB;
  glm::vec3 maxB = positionB + halfB;
  return maxA.x >= minB.x && minA.x <= maxB.x && maxA.y >= minB.y && minA.y <= maxB.y && maxA.z >= minB.z && minA.z <= maxB.z;
}

// Overlapping check with position and size
bool AABB::IsOverlapping(const glm::vec3 &position, glm::vec3 &size) const
{
  Logger::LogTrace(Logger::Module::AABB, "bool IsOverlapping(const glm::vec3 &position, glm::vec3 &size) const");

  glm::vec3 half = size / 2.0f;
  glm::vec3 min = position - half;
  glm::vec3 max = position + half;
  return this->max.x >= min.x && this->min.x <= max.x && this->max.y >= min.y && this->min.y <= max.y && this->max.z >= min.z && this->min.z <= max.z;
}

// Overlapping check with AABB
bool AABB::IsOverlapping(const AABB &aabb) const
{
  Logger::LogTrace(Logger::Module::AABB, "bool IsOverlapping(const AABB &aabb) const");

  return this->max.x >= aabb.min.x && this->min.x <= aabb.max.x && this->max.y >= aabb.min.y && this->min.y <= aabb.max.y && this->max.z >= aabb.min.z && this->min.z <= aabb.max.z;
}

// Get vertex position
glm::vec3 AABB::GetVertex(const unsigned int &index) const
{
  Logger::LogTrace(Logger::Module::AABB, "glm::vec3 GetVertex(const unsigned int &index) const");

  return this->vertices[index];
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
