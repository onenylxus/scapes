////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "Biome.h"

const Biome::GenerationData &Biome::GetGenerationData() const
{
	Logger::LogTrace(ModuleData::Name::BIOME, "const Biome::GenerationData &Biome::GetGenerationData() const");

	return this->generationData;
}

void Biome::GetHeightMap(std::array<float, Chunk::chunkArea> &heightMap, const Chunk &chunk)
{
	Logger::LogTrace(ModuleData::Name::BIOME, "Biome::GetHeightMap(std::array<float, Chunk::chunkArea> &heightMap, const Chunk &chunk)");

	if (chunk.globalCoords == heightMapCoords)
	{
		for (int i = 0; i < heightMap.size(); ++i)
		{
			heightMap[i] = heightMapCache[i];
		}
		return;
	}

	for (int z = 0; z < Chunk::chunkSize; ++z)
	{
		for (int x = 0; x < Chunk::chunkSize; ++x)
		{
			float sample = 0.0f;
			float totalAmplitude = 0.0f;

			for (int i = 0; i < generationData.octaves; ++i)
			{
				float pow = std::pow(2.0f, i);
				float amplitude = 1.0f / pow;

				float xx = (x + chunk.globalCoords.x) / generationData.scale * pow;
				float zz = (z + chunk.globalCoords.z) / generationData.scale * pow;
				sample += ((glm::simplex(glm::vec2(xx, zz)) + 1.0f) / 2.0f) * amplitude;
				totalAmplitude += amplitude;
			}

			sample /= totalAmplitude;
			sample = (sample * generationData.maxHeight) + generationData.yOffset;

			heightMap[(z * Chunk::chunkSize) + x] = sample;
			heightMapCache[(z * Chunk::chunkSize) + x] = sample;
		}
	}

	heightMapCoords = chunk.globalCoords;
}

float Biome::GetHeightAt(const int &x, const int &z)
{
	Logger::LogTrace(ModuleData::Name::BIOME, "Biome::GetHeightAt(const int &x, const int &z)");

	float sample = 0.0f;
	float totalAmplitude = 0.0f;

	for (int i = 0; i < generationData.octaves; ++i)
	{
		float pow = std::pow(2.0f, i);
		float amplitude = 1.0f / pow;

		float xx = x / generationData.scale * pow;
		float zz = z / generationData.scale * pow;
		sample += ((glm::simplex(glm::vec2(xx, zz)) + 1.0f) / 2.0f) * amplitude;
		totalAmplitude += amplitude;
	}

	sample /= totalAmplitude;
	sample = (sample * generationData.maxHeight) + generationData.yOffset;
	return sample;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
