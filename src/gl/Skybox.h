////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include "../manager/ShaderManager.h"
#include "../gl/Mesh.h"
#include "Camera.h"
#include "Cubemap.h"
#include "Object.h"

class Skybox
{
public:
	Skybox(const char *path);
	virtual ~Skybox();

private:
	Cubemap *texture;
	Object *cube;

public:
	void Render(Camera &camera);

public:
	Shader *GetShader();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
