////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include "../gl/Shader.h"

class ShaderManager
{
private:
	static std::map<const char *, Shader *> graphicsShaders;
	static std::map<const char *, Shader *> geometryShaders;
	static std::map<const char *, Shader *> computeShaders;

public:
	static void Init();
	static void Destroy();

public:
	static Shader *SetShader(const char *path, Shader::Type type = Shader::Type::GRAPHICS);

public:
	static Shader *GetShader(const char *path, Shader::Type type = Shader::Type::GRAPHICS);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
