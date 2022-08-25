////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <vector>
#include <glm/glm.hpp>

// Mesh class
class Mesh
{
  // Mesh data
  public:
    struct Data
    {
      std::vector<float> vertices;
      std::vector<int> attr;
      std::vector<unsigned int> indices;

      void operator = (const Mesh::Data& that)
      {
        this->vertices = that.vertices;
        this->attr = that.attr;
        this->indices = that.indices;
      }
    };

  // Methods
  public:
    static Mesh::Data Skybox()
    {
      Mesh::Data data;
      data.vertices = std::vector<float>({
        // Left
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        // Right
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,

        // Top
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,

        // Bottom
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // Front
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        // Back
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
      });
      data.attr = std::vector<int>({ 3 });
      data.indices = std::vector<unsigned int>();
      return data;
    }
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
