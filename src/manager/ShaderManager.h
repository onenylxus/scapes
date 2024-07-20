////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include "../gl/Shader.h"

// Shader manager class
class ShaderManager
{
// Properties
private:
  static std::map<const char *, Shader *> graphicsShaders;
  static std::map<const char *, Shader *> geometryShaders;
  static std::map<const char *, Shader *> computeShaders;

// Methods
public:
  static void Init();
  static void Destroy();

// Setters
public:
  static Shader *SetShader(const char *path, Shader::Type type = Shader::Type::GRAPHICS);

// Getters
public:
  static Shader *GetShader(const char *path, Shader::Type type = Shader::Type::GRAPHICS);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
