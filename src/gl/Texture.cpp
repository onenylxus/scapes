////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "Texture.h"

// Constructor
Texture::Texture()
{
  Logger::LogTrace(Logger::Module::TEXTURE, "Texture()");

  this->texture = 0;
}

// Destructor
Texture::~Texture()
{
  Logger::LogTrace(Logger::Module::TEXTURE, "~Texture()");

  if (this->texture != 0)
  {
    glDeleteTextures(1, &this->texture);
  }
}

// Bind texture
void Texture::Bind(const unsigned int &index) const
{
  Logger::LogTrace(Logger::Module::TEXTURE, "void Bind(const unsigned int &index) const");

  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(GL_TEXTURE_2D, this->texture);
}

// Load texture
Texture::Data* Texture::Load(const char* path, const bool &flip)
{
  Logger::LogTrace(Logger::Module::TEXTURE, "Texture::Data* Load(const char* path, const bool &flip)");

  // Load data
  Texture::Data* data = new Texture::Data();
  stbi_set_flip_vertically_on_load(flip);
  data->data = stbi_load(path, &data->width, &data->height, &data->format, 0);

  // Check data
  if (data->data == nullptr)
  {
    delete data;
    return nullptr;
  }
  return data;
}

// Create texture
void Texture::Create(const Texture::Data &data)
{
  Logger::LogTrace(Logger::Module::TEXTURE, "void Create(const Texture::Data &data)");

  int format = data.format == 3 ? GL_RGB : GL_RGBA;
  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_2D, this->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, format, data.width, data.height, 0, format, GL_UNSIGNED_BYTE, data.data);
}

// Destroy texture
void Texture::Destroy(Texture::Data* data)
{
  Logger::LogTrace(Logger::Module::TEXTURE, "void Destroy(Texture::Data* data)");

  if (data)
  {
    stbi_image_free(data->data);
  }
}

// Get texture
int Texture::GetTexture() const
{
  Logger::LogTrace(Logger::Module::TEXTURE, "int GetTexture() const");

  return this->texture;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
