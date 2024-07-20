////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>
#include "../util/Logger.h"

// Texture class
class Texture
{
// Texture data
public:
  struct Data
  {
    int width;
    int height;
    int format;
    unsigned char *data;
  };

// Constructor and destructor
public:
  Texture();
  virtual ~Texture();

// Properties
protected:
  GLuint texture;

// Methods
public:
  virtual void Bind(const unsigned int &index = 0) const;

protected:
  Texture::Data *Load(const char *path, const bool &flip = true);
  virtual void Create(const Texture::Data &data);
  void Destroy(Texture::Data *data);

// Getters
public:
  int GetTexture() const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
