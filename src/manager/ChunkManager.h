////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <array>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../core/Engine.h"
#include "../gl/Camera.h"
#include "../gl/Object.h"
#include "../gl/Tilemap.h"
#include "../world/Chunk.h"
#include "ShaderManager.h"

// Prototypes
class Chunk;

// Chunk manager class
class ChunkManager
{
  public:
    friend class Chunk;

  // Constructor and destructor
  public:
    ChunkManager();
    virtual ~ChunkManager();

  // Properties
  private:
    unsigned int renderDistance;
    unsigned int destroyDistance;
    std::unordered_map<glm::ivec2, Chunk*> chunks;
    Chunk* cachedChunk;
    std::mutex mutex;
    std::thread* generationThread;
    Shader* solidShader;
    Shader* liquidShader;
    bool isAppEnding;

  // Methods
  public:
    void Update();
    void Render(Camera& camera);
    void Load();
    Chunk* Create(const glm::ivec2& index);
    Chunk* FindChunk(const glm::ivec2& index);

  private:
    Chunk* LockAndFindChunk(const glm::ivec2& index);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
