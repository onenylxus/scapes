////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../util/Logger.h"

// Shader class
class Shader
{
  // Shader types
  public:
    enum class Type
    {
      GRAPHICS,
      GEOMETRY,
      COMPUTE
    };

  // Constructor and destructor
  public:
    Shader();
    virtual ~Shader();

  // Properties
  private:
    GLint program;

  // Methods
  public:
    bool LoadGraphics(std::string vsPath, std::string fsPath);
    bool LoadGeometry(std::string path);
    bool LoadCompute(std::string path);
    void Use();

  private:
    std::string ReadCode(std::string path);
    bool CheckShaderStatus(GLuint id);
    bool CheckProgramStatus(GLuint id);
    bool CheckStatus(GLuint id, PFNGLGETSHADERIVPROC ivFunc, PFNGLGETSHADERINFOLOGPROC ilFunc, GLenum type);

  // Setters
  public:
    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);
    void SetMatrix2(const char* name, const glm::mat2& value);
    void SetMatrix3(const char* name, const glm::mat3& value);
    void SetMatrix4(const char* name, const glm::mat4& value);
    void SetVector2(const char* name, const glm::vec2& value);
    void SetVector3(const char* name, const glm::vec3& value);
    void SetVector4(const char* name, const glm::vec4& value);
    void SetTextureUnit(const char* name, const unsigned int& value);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
