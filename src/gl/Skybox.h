////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../manager/ShaderManager.h"
#include "Camera.h"
#include "Cubemap.h"
#include "Object.h"

// Skybox class
class Skybox
{
	// Constructor and destructor
public:
	Skybox(const char *path);
	virtual ~Skybox();

	// Properties
private:
	Cubemap *texture;
	Object *cube;

	// Methods
public:
	void Render(Camera &camera);

	// Getters
public:
	Shader *GetShader();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
