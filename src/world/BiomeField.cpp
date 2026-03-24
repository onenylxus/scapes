////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "BiomeField.h"
#include "World.h"

BiomeField::BiomeField()
{
    Logger::LogTrace(ModuleData::Name::BIOME_FIELD, "BiomeField()");

    name = "Field";
    generationData.structureDensity = 10;
    generationData.scale = 260.0f;
    generationData.yOffset = 10.0f;
}

BiomeField::~BiomeField()
{
    Logger::LogTrace(ModuleData::Name::BIOME_FIELD, "~BiomeField()");
}

BlockID BiomeField::GetBlock(const int &height) const
{
    Logger::LogTrace(ModuleData::Name::BIOME_FIELD, "BlockID GetBlock(const int &height) const");

    if (height == 0)
    {
        return BlockID::GRASS;
    }
    if (height > -3)
    {
        return BlockID::DIRT;
    }
    if (height > -100)
    {
        return BlockID::STONE;
    }
    return BlockID::AIR;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////