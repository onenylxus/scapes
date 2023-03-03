////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "BlockManager.h"

// Set default values
Tilemap* BlockManager::solidTexture = nullptr;
Tilemap* BlockManager::liquidTexture = nullptr;
Tilemap* BlockManager::gaseousTexture = nullptr;
std::vector<float> BlockManager::solidVertexData = std::vector<float>({
  // Left
  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

  // Right
  1.0f, 0.0f, 1.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,

  // Top
  1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,

  // Bottom
  0.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
  1.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,

  // Front
  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, -1.0f,
  1.0f, 1.0f, 0.0f,	0.0f, 0.0f, -1.0f,

  // Back
  0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
});
std::vector<float> BlockManager::liquidVertexData = std::vector<float>({
  // Left
  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.9f, 1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.9f, 0.0f, -1.0f, 0.0f, 0.0f,

  // Right
  1.0f, 0.0f, 1.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 0.9f, 0.0f,	1.0f, 0.0f, 0.0f,
  1.0f, 0.9f, 1.0f,	1.0f, 0.0f, 0.0f,

  // Top
  1.0f, 0.9f, 1.0f,	0.0f, 1.0f, 0.0f,
  1.0f, 0.9f, 0.0f,	0.0f, 1.0f, 0.0f,
  0.0f, 0.9f, 0.0f,	0.0f, 1.0f, 0.0f,
  0.0f, 0.9f, 1.0f,	0.0f, 1.0f, 0.0f,

  // Bottom
  0.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
  1.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,

  // Front
  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
  0.0f, 0.9f, 0.0f,	0.0f, 0.0f, -1.0f,
  1.0f, 0.9f, 0.0f,	0.0f, 0.0f, -1.0f,

  // Back
  0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
  1.0f, 0.9f, 1.0f,	0.0f, 0.0f, 1.0f,
  0.0f, 0.9f, 1.0f,	0.0f, 0.0f, 1.0f,
});
std::vector<float> BlockManager::gaseousVertexData = std::vector<float>({
  // Left
  0.8f, 0.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.2f, 0.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.2f, 1.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.8f, 1.0f, 0.2f,	0.0f, 1.0f, 0.0f,

  // Right
  0.2f, 0.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.8f, 0.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.8f, 1.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.2f, 1.0f, 0.2f,	0.0f, 1.0f, 0.0f,

  // Top
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,

  // Bottom
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,

  // Front
  0.8f, 0.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.2f, 0.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.2f, 1.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.8f, 1.0f, 0.8f,	0.0f, 1.0f, 0.0f,

  // Back
  0.2f, 0.0f, 0.8f,	0.0f, 1.0f, 0.0f,
  0.8f, 0.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.8f, 1.0f, 0.2f,	0.0f, 1.0f, 0.0f,
  0.2f, 1.0f, 0.8f,	0.0f, 1.0f, 0.0f,
});
std::vector<Block::Data> BlockManager::blocks;

// Init block manager
void BlockManager::Init()
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "void Init()");

  // Load textures
  BlockManager::solidTexture = new Tilemap("res/textures/solid.png", 1, 1);
  BlockManager::liquidTexture = new Tilemap("res/textures/liquid.png", 1, 1);
  BlockManager::gaseousTexture = new Tilemap("res/textures/gaseous.png", 1, 1);

  // Load block database
  BlockManager::LoadDatabase();
}

// Destroy block manager
void BlockManager::Destroy()
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "void Destroy()");

  delete BlockManager::solidTexture;
  BlockManager::solidTexture = nullptr;
  delete BlockManager::liquidTexture;
  BlockManager::liquidTexture = nullptr;
  delete BlockManager::gaseousTexture;
  BlockManager::gaseousTexture = nullptr;
}

// Load block database
void BlockManager::LoadDatabase()
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "void LoadDatabase()");

  BlockManager::blocks.reserve(1);
  BlockManager::blocks.push_back(Block::Data((int)BlockManager::Value::AIR, "Air", Block::TextureIndex()));
}

// Get tilemap
const Tilemap* BlockManager::GetTilemap(const Block::Type type)
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "const Tilemap* GetTilemap(const Block::Type type)");

  switch (type)
  {
    case Block::Type::SOLID:
      return BlockManager::solidTexture;

    case Block::Type::LIQUID:
      return BlockManager::liquidTexture;

    case Block::Type::GASEOUS:
      return BlockManager::gaseousTexture;

    default:
      return nullptr;
  }
}

// Get block data
const Block::Data* BlockManager::GetBlockData(const BlockManager::Value &value)
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "const Block::Data* GetBlockData(const BlockManager::Value &value)");

  return &BlockManager::blocks[(int)value];
}

// Get texture coordinates
void BlockManager::GetTextureCoords(const BlockManager::Value &value, const Block::Face &face, std::array<glm::vec2, 4> &coords)
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "void GetTextureCoords(const BlockManager::Value &value, const Block::Face &face, std::array<glm::vec2, 4> &coords)");

  const Block::Data* data = BlockManager::GetBlockData(value);
  switch (data->textureType)
  {
    case Block::Type::SOLID:
      BlockManager::solidTexture->GetSpriteCoordinates(data->texture[(unsigned int)face], coords);
      break;

    case Block::Type::LIQUID:
      BlockManager::liquidTexture->GetSpriteCoordinates(data->texture[(unsigned int)face], coords);
      break;

    case Block::Type::GASEOUS:
      BlockManager::gaseousTexture->GetSpriteCoordinates(data->texture[(unsigned int)face], coords);
  }
}

// Get mesh face
void BlockManager::GetMeshFace(const Block::Type &type, const Block::Face &face, const unsigned int &corner, const glm::vec3 &position, std::vector<float> &vertices)
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "void GetMeshFace(const Block::Type &type, const Block::Face &face, const unsigned int &corner, const glm::vec3 &position, std::vector<float> &vertices)");

  int i = (int)face * 24 + corner * 6;
  switch (type)
  {
    case Block::Type::SOLID:
      vertices.emplace_back(BlockManager::solidVertexData[i] + position.x);
      vertices.emplace_back(BlockManager::solidVertexData[i + 1] + position.y);
      vertices.emplace_back(BlockManager::solidVertexData[i + 2] + position.z);
      vertices.emplace_back(BlockManager::solidVertexData[i + 3]);
      vertices.emplace_back(BlockManager::solidVertexData[i + 4]);
      vertices.emplace_back(BlockManager::solidVertexData[i + 5]);
      break;

    case Block::Type::LIQUID:
      vertices.emplace_back(BlockManager::liquidVertexData[i] + position.x);
      vertices.emplace_back(BlockManager::liquidVertexData[i + 1] + position.y);
      vertices.emplace_back(BlockManager::liquidVertexData[i + 2] + position.z);
      vertices.emplace_back(BlockManager::liquidVertexData[i + 3]);
      vertices.emplace_back(BlockManager::liquidVertexData[i + 4]);
      vertices.emplace_back(BlockManager::liquidVertexData[i + 5]);
      break;

    case Block::Type::GASEOUS:
      vertices.emplace_back(BlockManager::gaseousVertexData[i] + position.x);
      vertices.emplace_back(BlockManager::gaseousVertexData[i + 1] + position.y);
      vertices.emplace_back(BlockManager::gaseousVertexData[i + 2] + position.z);
      vertices.emplace_back(BlockManager::gaseousVertexData[i + 3]);
      vertices.emplace_back(BlockManager::gaseousVertexData[i + 4]);
      vertices.emplace_back(BlockManager::gaseousVertexData[i + 5]);
  }
}

// Get mesh face size
int BlockManager::GetMeshFaceSize(const Block::Type &type)
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "int GetMeshFaceSize(const Block::Type &type)");

  return type == Block::Type::GASEOUS ? 4 : 6;
}

// Get block value size
int BlockManager::GetValueSize()
{
  Logger::LogTrace(Logger::Module::BLOCK_MANAGER, "int GetValueSize()");

  return (int)BlockManager::Value::_VALUE_SIZE;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
