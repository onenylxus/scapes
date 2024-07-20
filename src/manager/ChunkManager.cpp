////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "ChunkManager.h"

// Constructor
ChunkManager::ChunkManager()
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "ChunkManager()");

  // Load shaders
  this->solidShader = ShaderManager::SetShader("solid", Shader::Type::GRAPHICS);
  this->liquidShader = ShaderManager::SetShader("liquid", Shader::Type::GRAPHICS);

  // Setup generation thread
  this->generationThread = new std::thread(&ChunkManager::Load, this);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  // Set properties
  this->renderDistance = 15;
  this->destroyDistance = this->renderDistance + 5;
  this->isAppEnding = false;
}

// Destructor
ChunkManager::~ChunkManager()
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "~ChunkManager()");

  // Destroy generation thread
  if (this->generationThread != nullptr)
  {
    this->isAppEnding = true;
    this->generationThread->join();
    delete this->generationThread;
  }

  // Clear chunks
  std::unordered_map<glm::ivec2, Chunk *>::iterator it = this->chunks.begin();
  for (; it != this->chunks.end();)
  {
    if (it->second != nullptr)
    {
      delete it->second;
      it->second = nullptr;

      if (it == this->chunks.end())
      {
        this->chunks.erase(it);
        break;
      }
      else
      {
        it = this->chunks.erase(it);
      }
    }
  }
}

// Update function
void ChunkManager::Update()
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "void Update()");
}

// Render function
void ChunkManager::Render(Camera &camera)
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "void Render(Camera &camera)");
}

// Load chunks
void ChunkManager::Load()
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "void Load()");

  // Setup mutex lock
  std::unique_lock<std::mutex> lock(this->mutex);
  lock.unlock();

  glm::ivec2 last = glm::ivec2(0);
  while (!this->isAppEnding)
  {
    for (int i = 0; i <= this->renderDistance; i++)
    {
      int minX = last.x - i;
      int maxX = last.x + i;
      int minZ = last.y - i;
      int maxZ = last.y + i;

      for (int z = minZ; z <= maxZ; z++)
      {
        for (int x = minX; x <= maxX; x++)
        {
          Chunk *chunk = Create(glm::ivec2(x, z));
        }
      }

      if (this->isAppEnding)
      {
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

// Create chunk
Chunk *ChunkManager::Create(const glm::ivec2 &index)
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "void Create(const glm::ivec2 &index)");

  // Check existing chunk
  Chunk *chunk = LockAndFindChunk(index);
  if (chunk != nullptr)
  {
    return chunk;
  }

  // Create chunk
  std::unique_lock<std::mutex> lock(this->mutex);
  chunk = new Chunk(index, *this);
  this->chunks.emplace(index, chunk);
  return chunk;
}

// Find chunk by index
Chunk *ChunkManager::FindChunk(const glm::ivec2 &index)
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "Chunk *FindChunk(const glm::ivec2 &index)");

  auto iter = this->chunks.find(index);
  return iter != this->chunks.end() ? iter->second : nullptr;
}

// Find chunk by index with mutex lock
Chunk *ChunkManager::LockAndFindChunk(const glm::ivec2 &index)
{
  Logger::LogTrace(ModuleData::Name::CHUNK_MANAGER, "Chunk *LockAndFindChunk(const glm::ivec2 &index)");

  std::unique_lock<std::mutex> lock(this->mutex);
  return FindChunk(index);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
