////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../gl/Texture.h"

// Sprite class
class Sprite : public Texture
{
  // Constructor and destructor
  public:
    Sprite(const char* path);
    virtual ~Sprite() = default;

  // Methods
  private:
    bool Load(const char* path);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
