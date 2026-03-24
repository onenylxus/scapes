////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <chrono>
#include <queue>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../gl/AABB.h"
#include "../gl/Shader.h"
#include "../manager/BlockManager.h"

class ChunkManager;

class Chunk
{
public:
	friend class ChunkManager;
	friend class WorldGeneration;

private:
	enum class Neighbor
	{
		NORTH = 0,
		NORTH_EAST = 1,
		EAST = 2,
		SOUTH_EAST = 3,
		SOUTH = 4,
		SOUTH_WEST = 5,
		WEST = 6,
		NORTH_WEST = 7
	};

public:
	Chunk(glm::ivec2 index, ChunkManager &manager);
	virtual ~Chunk();

public:
	static const unsigned int chunkSize = 16;
	static const unsigned int chunkArea = Chunk::chunkSize * Chunk::chunkSize;
	static const unsigned int chunkHeight = 128;
	static const unsigned int chunkVolume = Chunk::chunkArea * Chunk::chunkHeight;

private:
	glm::ivec2 neighborOffset[8] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

public:
	glm::ivec2 localCoords;
	glm::vec3 globalCoords;
	bool isDirty;
	bool hasData;
	int maxHeight;
	BlockID blocks[Chunk::chunkVolume];
	ChunkManager *manager;
	Chunk *neighbors[8];
	AABB *aabb;

public:
	BlockID GetBlock(const glm::ivec3 &position) const;

public:
	void SetBlock(const glm::ivec3 &position, const BlockID &blockID);

private:
	void SetDirty();

public:
	void RenderSolid(Shader &solidShader);
	void RenderLiquid(Shader &liquidShader);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
