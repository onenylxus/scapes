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
    typedef std::vector<float> VertexData;
    typedef std::vector<int> AttributeData;
    typedef std::vector<unsigned int>IndexData;
    struct Data
    {
      Mesh::VertexData vertices;
      Mesh::AttributeData attr;
      Mesh::IndexData indices;

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
      data.vertices = Mesh::VertexData({
        // Left
        -1.0f, -1.0f, -1.0f,
        -1.0f, +1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,

        -1.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f,

        // Right
        +1.0f, -1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f,

        +1.0f, +1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,
        +1.0f, +1.0f, +1.0f,

        // Top
        -1.0f, +1.0f, -1.0f,
        +1.0f, +1.0f, -1.0f,
        -1.0f, +1.0f, +1.0f,

        +1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, -1.0f,

        // Bottom
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f,

        +1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f,

        // Front
        -1.0f, +1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,

        +1.0f, -1.0f, -1.0f,
        +1.0f, +1.0f, -1.0f,
        -1.0f, +1.0f, -1.0f,

        // Back
        -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f,

        +1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f,
      });
      data.attr = Mesh::AttributeData({ 3 });
      data.indices = Mesh::IndexData();
      return data;
    }

    static Mesh::Data Cube()
    {
      Mesh::Data data;
      data.vertices = Mesh::VertexData({
        // Left
        -1.0f, -1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +1.0f,
        -1.0f, +1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +0.0f,

        -1.0f, +1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f,
        -1.0f, -1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +0.0f,
        -1.0f, +1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +1.0f,

        // Right
        +1.0f, -1.0f, +1.0f, +1.0f, +0.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, +1.0f, +1.0f, +1.0f, +0.0f, +0.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f, +1.0f, +0.0f, +0.0f, +0.0f, +0.0f,

        +1.0f, +1.0f, -1.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f,
        +1.0f, -1.0f, -1.0f, +1.0f, +0.0f, +0.0f, +0.0f, +0.0f,
        +1.0f, +1.0f, +1.0f, +1.0f, +0.0f, +0.0f, +1.0f, +1.0f,

        // Top
        -1.0f, +1.0f, -1.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, +1.0f, -1.0f, +0.0f, +1.0f, +0.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f, +0.0f, +1.0f, +0.0f, +0.0f, +0.0f,

        +1.0f, +1.0f, +1.0f, +0.0f, +1.0f, +0.0f, +1.0f, +0.0f,
        -1.0f, +1.0f, +1.0f, +0.0f, +1.0f, +0.0f, +0.0f, +0.0f,
        +1.0f, +1.0f, -1.0f, +0.0f, +1.0f, +0.0f, +1.0f, +1.0f,

        // Bottom
        -1.0f, -1.0f, -1.0f, +0.0f, -1.0f, +0.0f, +0.0f, +0.0f,
        -1.0f, -1.0f, +1.0f, +0.0f, -1.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, -1.0f, -1.0f, +0.0f, -1.0f, +0.0f, +1.0f, +0.0f,

        +1.0f, -1.0f, -1.0f, +0.0f, -1.0f, +0.0f, +1.0f, +0.0f,
        -1.0f, -1.0f, +1.0f, +0.0f, -1.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +0.0f, -1.0f, +0.0f, +1.0f, +1.0f,

        // Front
        -1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +1.0f, +0.0f,
        +1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f,

        +1.0f, -1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f,
        +1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +1.0f,
        -1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +1.0f, +1.0f,

        // Back
        -1.0f, -1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f,
        -1.0f, +1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +1.0f, +0.0f,

        +1.0f, +1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +1.0f, +0.0f,
        -1.0f, +1.0f, +1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +1.0f
      });
      data.attr = Mesh::AttributeData({ 3, 3, 2 });
      data.indices = Mesh::IndexData();
      return data;
    }
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
