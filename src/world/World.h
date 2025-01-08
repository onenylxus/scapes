////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../gl/Skybox.h"
#include "../manager/BlockManager.h"
#include "../manager/EntityManager.h"
#include "../view/Camera3D.h"
#include "Entity.h"

// World class
class World
{
	// Constructor and destructor
public:
	World();
	virtual ~World();

	// Properties
private:
	Skybox *skybox;

	// Methods
public:
	void Update();
	void Render();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
