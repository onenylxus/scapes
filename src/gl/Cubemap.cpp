////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Cubemap.h"

// Constructor
Cubemap::Cubemap(const char *path)
{
  Logger::LogTrace(ModuleData::Name::CUBEMAP, "Cubemap(const char *path)");

  this->Load(path);
}

// Destructor
Cubemap::~Cubemap()
{
  Logger::LogTrace(ModuleData::Name::CUBEMAP, "~Cubemap()");

  glDeleteTextures(1, &this->texture);
}

// Bind texture
void Cubemap::Bind(const unsigned int &index) const
{
  Logger::LogTrace(ModuleData::Name::CUBEMAP, "void Bind(const unsigned int &index) const");

  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
}

// Load texture
void Cubemap::Load(const char *path)
{
  Logger::LogTrace(ModuleData::Name::CUBEMAP, "void Load(const char *path)");

  // Load data
  std::string paths[6] = {"left.jpg", "right.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
  Texture::Data *data = new Texture::Data();
  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

  for (int i = 0; i < 6; i++)
  {
    std::string finalPath = std::string(path) + paths[i];
    data = Texture::Load(finalPath.c_str(), false);
    if (data == nullptr)
    {
      Logger::LogError(ModuleData::Name::CUBEMAP, "Texture failed to load: %s", finalPath.c_str());
      return;
    }

    // Create texture
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, data->width, data->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Destroy texture
    this->Destroy(data);
    delete data;
  }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
