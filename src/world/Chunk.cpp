////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "Chunk.h"

// Constructor
Chunk::Chunk(glm::ivec2 index, ChunkManager &manager)
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "Chunk(const glm::ivec2 index, ChunkManager &manager)");

	this->manager = &manager;
	this->globalCoords = glm::vec3(index.x * Chunk::chunkSize, 0.0f, index.y * Chunk::chunkSize);
	this->aabb = new AABB(glm::vec3(this->globalCoords.x + Chunk::chunkSize / 2.0f, Chunk::chunkHeight / 2.0f, this->globalCoords.z + Chunk::chunkSize / 2.0f), glm::vec3(Chunk::chunkSize, Chunk::chunkHeight, Chunk::chunkSize));

	for (int i = 0; i < 8; ++i)
	{
		this->neighbors[i] = nullptr;
	}
}

// Destructor
Chunk::~Chunk()
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "~Chunk()");

	delete this->aabb;

	for (int i = 0; i < 8; ++i)
	{
		this->neighbors[i] = nullptr;
	}
}

// Get block
BlockID Chunk::GetBlock(const glm::ivec3 &position) const
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "BlockID GetBlock(const glm::ivec3 &position) const");

	if (position.x < 0 || position.x >= Chunk::chunkSize || position.y < 0 || position.y >= Chunk::chunkHeight || position.z < 0 || position.z >= Chunk::chunkSize)
	{
		return BlockID::AIR;
	}
	return this->blocks[position.y * Chunk::chunkArea + position.z * Chunk::chunkSize + position.x];
}

// Set block
void Chunk::SetBlock(const glm::ivec3 &position, const BlockID &blockID)
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "void SetBlock(const glm::ivec3 &position, const BlockID &blockID)");

	if (position.x < 0 || position.x >= Chunk::chunkSize || position.y < 0 || position.y >= Chunk::chunkHeight || position.z < 0 || position.z >= Chunk::chunkSize)
	{
		return;
	}
	this->blocks[position.y * Chunk::chunkArea + position.z * Chunk::chunkSize + position.x] = blockID;
	this->SetDirty();
}

// Set dirty
void Chunk::SetDirty()
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "void SetDirty()");

	this->isDirty = true;
}

// Render with solid shader
void Chunk::RenderSolid(Shader &solidShader)
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "void RenderSolid(Shader &solidShader)");
}

// Render with liquid shader
void Chunk::RenderLiquid(Shader &liquidShader)
{
	Logger::LogTrace(ModuleData::Name::CHUNK, "void RenderLiquid(Shader &liquidShader)");
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
