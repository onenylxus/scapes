////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <array>
#include <chrono>
#include <queue>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../gl/AABB.h"
#include "../gl/Shader.h"
#include "../manager/BlockManager.h"

// Prototypes
class ChunkManager;

// Chunk class
class Chunk
{
  public:
    friend class ChunkManager;

  // Chunk neighbors
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

  // Constructor and destructor
  public:
    Chunk(glm::ivec2 index, ChunkManager& manager);
    virtual ~Chunk();

  // Properties
  public:
    static const unsigned int chunkSize = 16;
    static const unsigned int chunkArea = Chunk::chunkSize * Chunk::chunkSize;
    static const unsigned int chunkHeight = 128;
    static const unsigned int chunkVolume = Chunk::chunkArea * Chunk::chunkHeight;

  public:
    glm::ivec2 localCoords;
    glm::vec3 globalCoords;
    bool isDirty;
    int maxHeight;
    BlockManager::Value blocks[Chunk::chunkVolume];
    ChunkManager* manager;
    Chunk* neighbors[8];
    AABB* aabb;

  private:
    glm::ivec2 neighborOffset[8] = {{ 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }};

  // Methods
  public:
    void RenderSolid(Shader& solidShader);
    void RenderLiquid(Shader& liquidShader);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
