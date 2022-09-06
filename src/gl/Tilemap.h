////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include "Sprite.h"

// Tilemap class
class Tilemap
{
  // Constructor and destructor
  public:
    Tilemap(const char* path, const unsigned int &rows, const unsigned int &columns);
    virtual ~Tilemap();

  // Properties
  private:
    Sprite* texture;
    unsigned int rows;
    unsigned int columns;
    float tileWidth;
    float tileHeight;

  // Methods
  public:
    void Bind(const unsigned int &index = 0) const;

  // Getters
  public:
    void GetSpriteCoordinates(const unsigned int &index, std::array<glm::vec2, 4> &coords) const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
