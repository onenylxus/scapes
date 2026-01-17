////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include "../manager/BlockManager.h"
#include "Chunk.h"

class Biome
{
public:
	struct GenerationData
	{
		unsigned int structureDensity = 150;
		unsigned int octaves = 5;
		float scale = 128.0f;
		float maxHeight = 48.0f;
		float yOffset = 0.0f;
	};

protected:
	std::string name;
	Biome::GenerationData generationData = Biome::GenerationData();
	glm::vec3 heightMapCoords = glm::vec3(std::numeric_limits<float>::max());
	std::array<float, Chunk::chunkArea> heightMapCache = std::array<float, Chunk::chunkArea>();

public:
	virtual BlockID GetBlock(const int &height) const = 0;
	virtual void AddStructure(const glm::vec3 &position, std::array<BlockID, Chunk::chunkVolume> &chunkBlocks, std::vector<glm::vec3> &outPos, std::vector<BlockID> &outBlocks) {};

public:
	const Biome::GenerationData &GetGenerationData() const;
	void GetHeightMap(std::array<float, Chunk::chunkArea> &heightMap, const Chunk &chunk);
	float GetHeightAt(const int &x, const int &z);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
