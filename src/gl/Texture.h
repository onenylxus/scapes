////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

// Texture data struct
struct TextureData
{
  int width;
  int height;
  int format;
  unsigned char *data;
};

// Texture class
class Texture
{
  // Constructor and destructor
  public:
    Texture();
    virtual ~Texture();

  // Properties
  private:
    GLuint texture;

  // Methods
  public:
    virtual void Bind(const unsigned int &index = 0);

  protected:
    TextureData* Load(const char* path);
    virtual void Create(const TextureData &data);
    void Destroy(TextureData* data);

  // Getters
  public:
    int GetTexture();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
