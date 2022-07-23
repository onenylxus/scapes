////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Shader.h"

// Constructor
Shader::Shader()
{
  this->program = -1;
}

// Destructor
Shader::~Shader()
{
  if (this->program != 0)
  {
    glDeleteProgram(this->program);
  }
}

// Load graphics shader
bool Shader::LoadGraphics(std::string vsPath, std::string fsPath)
{
  // Create vertex shader
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vCode = this->ReadCode(vsPath).c_str();
  glShaderSource(vs, 1, &vCode, NULL);
  glCompileShader(vs);

  // Check vertex shader status
  if (!this->CheckShaderStatus(vs))
  {
    return false;
  }

  // Create fragment shader
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fCode = this->ReadCode(fsPath).c_str();
  glShaderSource(fs, 1, &fCode, NULL);
  glCompileShader(fs);

  // Check fragment shader status
  if (!this->CheckShaderStatus(fs))
  {
    return false;
  }

  // Compile shaders into program
  this->program = glCreateProgram();
  glAttachShader(this->program, vs);
  glAttachShader(this->program, fs);
  glLinkProgram(this->program);

  // Check program status
  if (!this->CheckProgramStatus(this->program))
  {
    return false;
  }

  // Finalize
  glDeleteShader(vs);
  glDeleteShader(fs);
  return true;
}

// Load geometry shader
bool Shader::LoadGeometry(std::string path)
{
  // Create geometry shader
  GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
  const GLchar* gCode = this->ReadCode(path).c_str();
  glShaderSource(gs, 1, &gCode, NULL);
  glCompileShader(gs);

  // Check geometry shader status
  if (!this->CheckShaderStatus(gs))
  {
    return false;
  }

  // Compile shader into program
  this->program = glCreateProgram();
  glAttachShader(this->program, gs);
  glLinkProgram(this->program);

  // Check program status
  if (!this->CheckProgramStatus(this->program))
  {
    return false;
  }

  // Finalize
  glDeleteShader(gs);
  return true;
}

// Load compute shader
bool Shader::LoadCompute(std::string path)
{
  // Create compute shader
  GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
  const GLchar* cCode = this->ReadCode(path).c_str();
  glShaderSource(cs, 1, &cCode, NULL);
  glCompileShader(cs);

  // Check compute shader status
  if (!this->CheckProgramStatus(cs))
  {
    return false;
  }

  // Compile shader into program
  this->program = glCreateProgram();
  glAttachShader(this->program, cs);
  glLinkProgram(this->program);

  // Check program status
  if (!this->CheckProgramStatus(this->program))
  {
    return false;
  }

  // Finalize
  glDeleteShader(cs);
  return true;
}

// Use program
void Shader::Use()
{
  glUseProgram(this->program);
}

// Read shader code
std::string Shader::ReadCode(std::string path)
{
  std::ifstream input(path.c_str());
  if (!input.good())
  {
    std::cout << "File failed to open: " << path << std::endl;
    exit(1);
  }
  return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

// Check shader status
bool Shader::CheckShaderStatus(GLuint id)
{
  return this->CheckStatus(id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

// Check program status
bool Shader::CheckProgramStatus(GLuint id)
{
  return this->CheckStatus(id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

// Check status
bool Shader::CheckStatus(GLuint id, PFNGLGETSHADERIVPROC ivFunc, PFNGLGETSHADERINFOLOGPROC ilFunc, GLenum type)
{
  // Run status function
  GLint status;
  ivFunc(id, type, &status);

  // Check status
  if (status != GL_TRUE)
  {
    // Create buffer
    GLint ilLength;
    ivFunc(id, GL_INFO_LOG_LENGTH, &ilLength);
    GLchar* buffer = new GLchar[ilLength];

    // Write log
    GLsizei bufferSize;
    ilFunc(id, ilLength, &bufferSize, buffer);
    std::cout << buffer << std::endl;

    // Delete buffer
    delete[] buffer;
    return false;
  }
  return true;
}

// Set uniform float value
void Shader::SetFloat(const char* name, float value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform float location: " << name << std::endl;
    return;
  }
  glUniform1f(loc, value);
}

// Set uniform integer value
void Shader::SetInt(const char* name, int value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform integer location: " << name << std::endl;
    return;
  }
  glUniform1i(loc, value);
}

// Set uniform matrix2 value
void Shader::SetMatrix2(const char* name, const glm::mat2& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform matrix2 location: " << name << std::endl;
    return;
  }
  glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform matrix3 value
void Shader::SetMatrix3(const char* name, const glm::mat3& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform matrix3 location: " << name << std::endl;
    return;
  }
  glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform matrix4 value
void Shader::SetMatrix4(const char* name, const glm::mat4& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform matrix4 location: " << name << std::endl;
    return;
  }
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform vector2 value
void Shader::SetVector2(const char* name, const glm::vec2& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform vector2 location: " << name << std::endl;
    return;
  }
  glUniform2fv(loc, 1, &value[0]);
}

// Set uniform vector3 value
void Shader::SetVector3(const char* name, const glm::vec3& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform vector3 location: " << name << std::endl;
    return;
  }
  glUniform3fv(loc, 1, &value[0]);
}

// Set uniform vector4 value
void Shader::SetVector4(const char* name, const glm::vec4& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform vector4 location: " << name << std::endl;
    return;
  }
  glUniform4fv(loc, 1, &value[0]);
}

// Set uniform texture unit value
void Shader::SetTextureUnit(const char* name, const unsigned int& value)
{
  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    std::cout << "Failed to get uniform texture unit location: " << name << std::endl;
    return;
  }
  glUniform1i(loc, value);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
