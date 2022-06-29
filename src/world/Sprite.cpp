////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Sprite.h"

// Constructor
Sprite::Sprite(const char* path)
{
  this->Load(path);
}

// Load texture
bool Sprite::Load(const char* path)
{
  // Load data
  TextureData* data = Texture::Load(path);
  if (data == nullptr)
  {
    std::cout << "Texture failed to load: " << path << std::endl;
    return false;
  }

  // Create texture
  this->Create(*data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Destory data
  this->Destroy(data);
  delete data;
  return true;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
