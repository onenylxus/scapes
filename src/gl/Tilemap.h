////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include "Sprite.h"

class Tilemap
{
public:
	Tilemap(const char *path, const unsigned int &rows, const unsigned int &columns);
	virtual ~Tilemap();

private:
	Sprite *texture;
	unsigned int rows;
	unsigned int columns;
	float tileWidth;
	float tileHeight;

public:
	void Bind(const unsigned int &index = 0) const;

public:
	void GetSpriteCoordinates(const unsigned int &index, std::array<glm::vec2, 4> &coords) const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
