////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <string>
#include "Texture.h"

// Cubemap class
class Cubemap : public Texture
{
  // Constructor and destructor
  public:
    Cubemap(const char* path);
    virtual ~Cubemap();

  // Methods
  public:
    void Bind(const unsigned int &index = 0) const override;

  private:
    void Load(const char* path);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
