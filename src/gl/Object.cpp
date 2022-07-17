////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Object.h"

// Constructor
Object::Object(const glm::vec3 &position, const std::vector<float> &data, const std::vector<int> &attr, const std::vector<unsigned int> &indices)
{
  // Set transform
  this->transform = new Transform();
  this->transform->SetPosition(position);

  // Create array buffers
  glGenVertexArrays(1, &this->data.vao);
  glGenBuffers(1, &this->data.vbo);
  if (indices.size() > 0)
  {
    glGenBuffers(1, &this->data.ebo);
  }

  // Bind array buffers
  glBindVertexArray(this->data.vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->data.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);

  // Bind indices
  if (indices.size() > 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->data.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    int attrCount = 0;
    for (int i = 0; i < attr.size(); i++)
    {
      attrCount += attr[i];
    }

    int offset = 0;
    for (int i = 0; i < attr.size(); i++)
    {
      glVertexAttribPointer(i, attr[i], GL_FLOAT, GL_FALSE, sizeof(float) * attrCount, (void*)(sizeof(float) * offset));
      glEnableVertexAttribArray(i);
      offset += attr[i];
    }
    this->data.size = indices.size() > 0 ? indices.size() : sizeof(float) * data.size() / attrCount;
  }

  // Unbind array buffers
  glBindVertexArray(0);
}

// Destructor
Object::~Object()
{
  // Delete array buffers
  if (this->data.vao != 0)
  {
    glDeleteVertexArrays(1, &this->data.vao);
    glDeleteBuffers(1, &this->data.vbo);
    if (this->data.ebo != 0)
    {
      glDeleteBuffers(1, &this->data.ebo);
    }
  }
}

// Bind vertex array
void Object::BindVAO() const
{
  glBindVertexArray(this->data.vao);
}

// Bind vertex buffer
void Object::BindVBO() const
{
  glBindBuffer(GL_ARRAY_BUFFER, this->data.vbo);
}

// Render object with camera
void Object::Render(Camera& camera)
{
  // Check shader exists
  if (!this->shader)
  {
    return;
  }

  // Set shader values
  this->BindVAO();
  this->shader->SetMatrix4("uModel", this->transform->GetMatrix());
  this->shader->SetMatrix4("uProjectionView", camera.GetProjectionView());

  // Draw object
  if (this->data.ebo <= 0)
  {
    glDrawArrays(GL_TRIANGLES, 0, this->data.size);
  }
  else
  {
    glDrawElements(GL_TRIANGLES, this->data.size, GL_UNSIGNED_INT, 0);
  }
}

// Render object without camera
void Object::Render()
{
  // Check shader exists
  if (!this->shader)
  {
    return;
  }

  // Draw object
  this->BindVAO();
  if (this->data.ebo <= 0)
  {
    glDrawArrays(GL_TRIANGLES, 0, this->data.size);
  }
  else
  {
    glDrawElements(GL_TRIANGLES, this->data.size, GL_UNSIGNED_INT, 0);
  }
}

// Set shader
void Object::SetShader(Shader* shader)
{
  this->shader = shader;
}

// Get shader
Shader* Object::GetShader() const
{
  return this->shader;
}

// Get position
glm::vec3 Object::GetPosition()
{
  return this->transform->GetPosition();
}

// Get transform
Transform* Object::GetTransform()
{
  return this->transform;
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
