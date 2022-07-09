////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Shader.h"

// Object class
class Object
{
  // Object data
  public:
    struct Data
    {
      unsigned int vao;
      unsigned int vbo;
      unsigned int ebo;
      int size;
    };

  // Constructor and destructor
  public:
    Object(const glm::vec3 &position, const std::vector<float> &data, const std::vector<int> &attr, const std::vector<unsigned int> &indices = std::vector<unsigned int>());
    virtual ~Object();

  // Properties
  private:
    Object::Data data;
    Shader* shader;

  // Methods
  public:
    void BindVAO() const;
    void BindVBO() const;
    void Render(Camera &camera);

  // Setters
  public:
    void SetShader(Shader* shader);

  // Getters
  public:
    Shader* GetShader() const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
