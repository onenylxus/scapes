////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <array>

// Block class
class Block
{
  // Block types
  public:
    enum class Type
    {
      SOLID,
      LIQUID,
      GASEOUS
    };

  // Block faces
  public:
    enum class Face
    {
      LEFT,
      RIGHT,
      TOP,
      BOTTOM,
      FRONT,
      BACK
    };

  // Texture index
  public:
    struct TextureIndex
    {
      std::array<unsigned int, 6> indices;

      TextureIndex(const unsigned int& left = 0, const unsigned int& right = 0, const unsigned int& top = 0, const unsigned int& bottom = 0, const unsigned int& front = 0, const unsigned int& back = 0)
      {
        this->indices = std::array<unsigned int, 6>();
        this->indices[(int)Block::Face::LEFT] = left;
        this->indices[(int)Block::Face::RIGHT] = right;
        this->indices[(int)Block::Face::TOP] = top;
        this->indices[(int)Block::Face::BOTTOM] = bottom;
        this->indices[(int)Block::Face::FRONT] = front;
        this->indices[(int)Block::Face::BACK] = back;
      }

      void operator = (const Block::TextureIndex& that)
      {
        for (int i = 0; i < 6; i++)
        {
          this->indices[i] = that.indices[i];
        }
      }

      unsigned int operator [] (unsigned int i) const
      {
        return i >= 0 && i < 6 ? this->indices[i] : 0;
      }
    };

  // Block data
  public:
    struct Data
    {
      int id;
      const char* name;
      Block::TextureIndex texture;
      Block::Type meshType;
      Block::Type textureType;

      Data(int id, const char *name, Block::TextureIndex texture, Block::Type meshType = Block::Type::SOLID, Block::Type textureType = Block::Type::SOLID)
      {
        this->id = id;
        this->name = name;
        this->texture = texture;
        this->meshType = meshType;
        this->textureType = textureType;
      }
    };
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
