////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Shader.h"

// Constructor
Shader::Shader()
{
  Logger::LogTrace(ModuleData::Name::SHADER, "Shader()");

  this->program = -1;
}

// Destructor
Shader::~Shader()
{
  Logger::LogTrace(ModuleData::Name::SHADER, "~Shader()");

  if (this->program != 0)
  {
    glDeleteProgram(this->program);
  }
}

// Load graphics shader
bool Shader::LoadGraphics(std::string vsPath, std::string fsPath)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "bool LoadGraphics(std::string vsPath, std::string fsPath)");

  // Create vertex shader
  std::string vStr = this->ReadCode(vsPath);
  const GLchar* vCode = vStr.c_str();
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vCode, NULL);
  glCompileShader(vs);

  // Check vertex shader status
  if (!this->CheckShaderStatus(vs))
  {
    return false;
  }

  // Create fragment shader
  std::string fStr = this->ReadCode(fsPath);
  const GLchar* fCode = fStr.c_str();
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
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
  Logger::LogTrace(ModuleData::Name::SHADER, "bool LoadGeometry(std::string path)");

  // Create geometry shader
  std::string gStr = this->ReadCode(path);
  const GLchar* gCode = gStr.c_str();
  GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
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
  Logger::LogTrace(ModuleData::Name::SHADER, "bool LoadCompute(std::string path)");

  // Create compute shader
  std::string cStr = this->ReadCode(path);
  const GLchar* cCode = cStr.c_str();
  GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
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
  Logger::LogTrace(ModuleData::Name::SHADER, "void Use()");

  glUseProgram(this->program);
}

// Read shader code
std::string Shader::ReadCode(std::string path)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "std::string ReadCode(std::string path)");

  std::ifstream input(path.c_str());
  if (!input.good())
  {
    Logger::LogError(ModuleData::Name::SHADER, "File failed to open: %s", path.c_str());
    exit(1);
  }
  return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

// Check shader status
bool Shader::CheckShaderStatus(GLuint id)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "bool CheckShaderStatus(GLuint id)");

  return this->CheckStatus(id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

// Check program status
bool Shader::CheckProgramStatus(GLuint id)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "bool CheckProgramStatus(GLuint id)");

  return this->CheckStatus(id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

// Check status
bool Shader::CheckStatus(GLuint id, PFNGLGETSHADERIVPROC ivFunc, PFNGLGETSHADERINFOLOGPROC ilFunc, GLenum type)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "bool CheckStatus(GLuint id, PFNGLGETSHADERIVPROC ivFunc, PFNGLGETSHADERINFOLOGPROC ilFunc, GLenum type)");

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
    Logger::LogDebug(ModuleData::Name::SHADER, "%s", buffer);

    // Delete buffer
    delete[] buffer;
    return false;
  }
  return true;
}

// Set uniform float value
void Shader::SetFloat(const char* name, float value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetFloat(const char* name, float value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform float location: %s", name);
    return;
  }
  glUniform1f(loc, value);
}

// Set uniform integer value
void Shader::SetInt(const char* name, int value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetInt(const char* name, int value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform integer location: %s", name);
    return;
  }
  glUniform1i(loc, value);
}

// Set uniform matrix2 value
void Shader::SetMatrix2(const char* name, const glm::mat2& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetMatrix2(const char* name, const glm::mat2& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform matrix2 location: %s", name);
    return;
  }
  glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform matrix3 value
void Shader::SetMatrix3(const char* name, const glm::mat3& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetMatrix3(const char* name, const glm::mat3& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform matrix3 location: %s", name);
    return;
  }
  glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform matrix4 value
void Shader::SetMatrix4(const char* name, const glm::mat4& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetMatrix4(const char* name, const glm::mat4& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform matrix4 location: %s", name);
    return;
  }
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// Set uniform vector2 value
void Shader::SetVector2(const char* name, const glm::vec2& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetVector2(const char* name, const glm::vec2& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform vector2 location: %s", name);
    return;
  }
  glUniform2fv(loc, 1, &value[0]);
}

// Set uniform vector3 value
void Shader::SetVector3(const char* name, const glm::vec3& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetVector3(const char* name, const glm::vec3& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform vector3 location: %s", name);
    return;
  }
  glUniform3fv(loc, 1, &value[0]);
}

// Set uniform vector4 value
void Shader::SetVector4(const char* name, const glm::vec4& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetVector4(const char* name, const glm::vec4& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform vector4 location: %s", name);
    return;
  }
  glUniform4fv(loc, 1, &value[0]);
}

// Set uniform texture unit value
void Shader::SetTextureUnit(const char* name, const unsigned int& value)
{
  Logger::LogTrace(ModuleData::Name::SHADER, "void SetTextureUnit(const char* name, const unsigned int& value)");

  this->Use();
  unsigned int loc = glGetUniformLocation(this->program, name);
  if (loc == -1)
  {
    Logger::LogError(ModuleData::Name::SHADER, "Failed to get uniform texture unit location: %s", name);
    return;
  }
  glUniform1i(loc, value);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
