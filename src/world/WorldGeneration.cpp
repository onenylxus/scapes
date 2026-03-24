////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "WorldGeneration.h"

WorldGeneration::WorldGeneration()
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "WorldGeneration()");

    srand(time(NULL));
}

WorldGeneration::~WorldGeneration()
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "~WorldGeneration()");

    delete this->field;
}

void WorldGeneration::Init()
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "void Init()");
}

unsigned int WorldGeneration::CreateChunkData(const Chunk &chunk, std::array<BlockID, Chunk::chunkVolume> &chunkBlocks)
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "unsigned int CreateChunkData(const Chunk& chunk, std::array<BlockID, Chunk::chunkVolume> &chunkBlocks)");

    if (chunk.hasData)
    {
        return 0;
    }

    CreateBiomeMap(chunk);
    CreateHeightMap(chunk, this->heightMap);

    glm::vec2 coords;
    for (int z = 0; z < Chunk::chunkSize; ++z)
    {
        for (int x = 0; x < Chunk::chunkSize; ++x)
        {
            coords = glm::vec2(chunk.globalCoords.x + x, chunk.globalCoords.z + z) / this->biomeScale;
            heightMap[z * Chunk::chunkSize + x] += glm::simplex(coords) * 20.0f;
        }
    }

    int maxHeight = glm::max((*std::max_element(this->heightMap.begin(), this->heightMap.end())) + 1.0f, 16.0f);
    for (int y = 0; y < maxHeight; ++y)
    {
        for (int z = 0; z < Chunk::chunkSize; ++z)
        {
            for (int x = 0; x < Chunk::chunkSize; ++x)
            {
                int blockIndex = y * Chunk::chunkArea + z * Chunk::chunkSize + x;
                int mapHeight = (int)this->heightMap[z * Chunk::chunkSize + x];
                int height = y - mapHeight;

                Biome *biome = this->field;
                BlockID block = biome->GetBlock(height);

                if (y == 0)
                {
                    chunkBlocks[blockIndex] = BlockID::GRASS;
                }

                if (chunkBlocks[blockIndex] == BlockID::AIR)
                {
                    chunkBlocks[blockIndex] = block;
                }
            }
        }
    }

    return maxHeight + 10;
}

void WorldGeneration::CreateBiomeMap(const Chunk &chunk)
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "void CreateBiomeMap(const Chunk& chunk)");

    for (int z = 0; z < Chunk::chunkSize; ++z)
    {
        for (int x = 0; x < Chunk::chunkSize; ++x)
        {
            this->biomeMap[z * Chunk::chunkSize + x] = (glm::simplex(glm::vec2(chunk.globalCoords.x + x, chunk.globalCoords.z + z) / this->biomeScale + 1.0f)) / 2.0f;
        }
    }
}

void WorldGeneration::CreateHeightMap(const Chunk &chunk, std::array<float, Chunk::chunkArea> &heightMap) const
{
    Logger::LogTrace(ModuleData::Name::WORLD_GENERATION, "void CreateHeightMap(const Chunk& chunk, std::array<float, Chunk::chunkArea> &heightMap) const");

    return this->field->GetHeightMap(heightMap, chunk);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////