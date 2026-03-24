////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <algorithm>
#include <cmath>
#include <vector>
#include "glm/gtc/noise.hpp"
#include "Chunk.h"
#include "BiomeField.h"

class ChunkManager;

class WorldGeneration
{
public:
    enum class BiomeIndex
    {
        FIELD,
    };

public:
    WorldGeneration();
    virtual ~WorldGeneration();

private:
    const float biomeScale = 512.0f;

    Biome *field = new BiomeField();

    std::array<float, Chunk::chunkArea> heightMap = std::array<float, Chunk::chunkArea>();
    std::array<float, Chunk::chunkArea> biomeMap = std::array<float, Chunk::chunkArea>();

public:
    static void Init();
    unsigned int CreateChunkData(const Chunk &chunk, std::array<BlockID, Chunk::chunkVolume> &chunkBlocks);

private:
    void CreateBiomeMap(const Chunk &chunk);
    void CreateHeightMap(const Chunk &chunk, std::array<float, Chunk::chunkArea> &heightMap) const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////