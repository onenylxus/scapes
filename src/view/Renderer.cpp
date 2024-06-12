////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Renderer.h"

// Set default values
std::vector<Renderer::Line> Renderer::lines = std::vector<Renderer::Line>();
Shader* Renderer::shader;

// Add line to renderer
void Renderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
  Logger::LogTrace(ModuleData::Name::RENDERER, "void Renderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)");

  // Create line
  Renderer::Line line = Renderer::Line();
  line.start = start;
  line.end = end;
  line.color = color;
  glm::vec3 vec[2] = { start, end };

  // Create array buffers
  glGenVertexArrays(1, &line.vao);
  glGenBuffers(1, &line.vbo);

  // Bind array buffers
  glBindVertexArray(line.vao);
  glBindBuffer(GL_ARRAY_BUFFER, line.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, &vec[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  // Push line to renderer
  Renderer::lines.push_back(line);
}

// Add box to renderer
void Renderer::AddBox(glm::vec3 position, glm::vec3 color)
{
  Logger::LogTrace(ModuleData::Name::RENDERER, "void Renderer::AddBox(glm::vec3 position, glm::vec3 color)");

  // Define values
  float offset = 0.5f;
  float xMin = position.x - offset;
  float xMax = position.x + offset;
  float yMin = position.y - offset;
  float yMax = position.y + offset;
  float zMin = position.z - offset;
  float zMax = position.z + offset;

  // Add lines to make a box
  AddLine(glm::floor(glm::vec3(xMin, yMin, zMin)), glm::floor(glm::vec3(xMax, yMin, zMin)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMin, zMin)), glm::floor(glm::vec3(xMax, yMax, zMin)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMax, zMin)), glm::floor(glm::vec3(xMin, yMax, zMin)), color);
  AddLine(glm::floor(glm::vec3(xMin, yMax, zMin)), glm::floor(glm::vec3(xMin, yMin, zMin)), color);
  AddLine(glm::floor(glm::vec3(xMin, yMin, zMin)), glm::floor(glm::vec3(xMin, yMin, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMin, zMin)), glm::floor(glm::vec3(xMax, yMin, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMax, zMin)), glm::floor(glm::vec3(xMax, yMax, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMin, yMax, zMin)), glm::floor(glm::vec3(xMin, yMax, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMin, yMin, zMax)), glm::floor(glm::vec3(xMax, yMin, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMin, zMax)), glm::floor(glm::vec3(xMax, yMax, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMax, yMax, zMax)), glm::floor(glm::vec3(xMin, yMax, zMax)), color);
  AddLine(glm::floor(glm::vec3(xMin, yMax, zMax)), glm::floor(glm::vec3(xMin, yMin, zMax)), color);
}

// Render with camera
void Renderer::Render(Camera &camera)
{
  Logger::LogTrace(ModuleData::Name::RENDERER, "void Renderer::Render(Camera &camera)");

  // Setup shader
  if (Renderer::shader == nullptr)
  {
    Renderer::shader = ShaderManager::SetShader("line");
  }
  Renderer::shader->SetMatrix4("uProjectionView", camera.GetProjectionView());
  Renderer::shader->SetMatrix4("uModel", glm::mat4(1.0f));

  // Draw lines
  for (int i = 0; i < Renderer::lines.size(); ++i)
  {
    Renderer::shader->SetVector3("uColor", Renderer::lines[i].color);
    glBindVertexArray(Renderer::lines[i].vao);
    glDrawArrays(GL_LINES, 0, 2);
  }
}

// Clear renderer
void Renderer::Clear()
{
  Logger::LogTrace(ModuleData::Name::RENDERER, "void Renderer::Clear()");

  // Delete buffers
  for (int i = 0; i < Renderer::lines.size(); ++i)
  {
    glDeleteBuffers(1, &Renderer::lines[i].vbo);
    glDeleteVertexArrays(1, &Renderer::lines[i].vao);
  }
  Renderer::lines.clear();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
