////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../gl/Tilemap.h"
#include "../world/Block.h"

// Block manager class
class BlockManager
{
  // Block values
  public:
    enum class Value {
      AIR,
      _VALUE_SIZE,
    };

  // Properties
  private:
    static Tilemap* solidTexture;
    static Tilemap* liquidTexture;
    static Tilemap* gaseousTexture;
    static std::vector<float> solidVertexData;
    static std::vector<float> liquidVertexData;
    static std::vector<float> gaseousVertexData;
    static std::vector<Block::Data> blocks;

  // Methods
  public:
    static void Init();
    static void Destroy();
    static void LoadDatabase();

  // Getters
  public:
    static const Tilemap* GetTilemap(const Block::Type type = Block::Type::SOLID);
    static const Block::Data* GetBlockData(const BlockManager::Value &value);
    static void GetTextureCoords(const BlockManager::Value &value, const Block::Face &face, std::array<glm::vec2, 4> &coords);
    static void GetMeshFace(const Block::Type &type, const Block::Face &face, const unsigned int &corner, const glm::vec3 &position, std::vector<float> &vertices);
    static int GetMeshFaceSize(const Block::Type &type);
    static int GetValueSize();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
