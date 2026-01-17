////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include "../world/World.h"
#include "Engine.h"

class Application : public Engine
{
private:
	static Application *app;
	World *world;

private:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnEnd() override;

public:
	static Application &GetApp();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
