////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Chunk.h"

// Constructor
Chunk::Chunk(glm::ivec2 index, ChunkManager& manager)
{
  Logger::LogTrace(Logger::Module::CHUNK, "Chunk(const glm::ivec2 index, ChunkManager& manager)");

  this->manager = &manager;
  this->globalCoords = glm::vec3(index.x * Chunk::chunkSize, 0.0f, index.y * Chunk::chunkSize);
  this->aabb = new AABB(glm::vec3(this->globalCoords.x + Chunk::chunkSize / 2.0f, Chunk::chunkHeight / 2.0f, this->globalCoords.z + Chunk::chunkSize / 2.0f), glm::vec3(Chunk::chunkSize, Chunk::chunkHeight, Chunk::chunkSize));

  for (int i = 0; i < 8; i++)
  {
    this->neighbors[i] = nullptr;
  }
}

// Destructor
Chunk::~Chunk()
{
  Logger::LogTrace(Logger::Module::CHUNK, "~Chunk()");

  delete this->aabb;

  for (int i = 0; i < 8; i++)
  {
    this->neighbors[i] = nullptr;
  }
}

// Render with solid shader
void Chunk::RenderSolid(Shader& solidShader)
{
  Logger::LogTrace(Logger::Module::CHUNK, "void RenderSolid(Shader& solidShader)");
}

// Render with liquid shader
void Chunk::RenderLiquid(Shader& liquidShader)
{
  Logger::LogTrace(Logger::Module::CHUNK, "void RenderLiquid(Shader& liquidShader)");
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
