////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../util/Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"

// Object class
class Object
{
  // Object data
  public:
    struct Data
    {
      unsigned int vao = 0;
      unsigned int vbo = 0;
      unsigned int ebo = 0;
      int size;
    };

  // Constructor and destructor
  public:
    Object(const glm::vec3 &position, const std::vector<float> &data, const std::vector<int> &attr, const std::vector<unsigned int> &indices = std::vector<unsigned int>());
    Object(const glm::vec3 &position, const Mesh::Data &data);
    virtual ~Object();

  // Properties
  private:
    Object::Data data;
    Transform* transform;
    Shader* shader;

  // Methods
  public:
    void BindVAO() const;
    void BindVBO() const;
    void Render(Camera& camera);
    void Render();

  // Setters
  public:
    void SetShader(Shader* shader);

  // Getters
  public:
    Shader* GetShader() const;
    glm::vec3 GetPosition();
    Transform* GetTransform();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
