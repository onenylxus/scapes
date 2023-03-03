////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "ShaderManager.h"

// Set default values
std::map<const char*, Shader*> ShaderManager::graphicsShaders;
std::map<const char*, Shader*> ShaderManager::geometryShaders;
std::map<const char*, Shader*> ShaderManager::computeShaders;

// Init shader manager
void ShaderManager::Init()
{
  Logger::LogTrace(Logger::Module::SHADER_MANAGER, "void Init()");

  ShaderManager::SetShader("base");
}

// Destroy shader manager
void ShaderManager::Destroy()
{
  Logger::LogTrace(Logger::Module::SHADER_MANAGER, "void Destroy()");

  // Destroy graphics shaders
  for (std::map<const char*, Shader*>::iterator i = ShaderManager::graphicsShaders.begin(); i != ShaderManager::graphicsShaders.end(); i++)
  {
    delete i->second;
    i->second = nullptr;
  }

  // Destroy geometry shaders
  for (std::map<const char*, Shader*>::iterator i = ShaderManager::geometryShaders.begin(); i != ShaderManager::geometryShaders.end(); i++)
  {
    delete i->second;
    i->second = nullptr;
  }

  // Destroy compute shaders
  for (std::map<const char*, Shader*>::iterator i = ShaderManager::computeShaders.begin(); i != ShaderManager::computeShaders.end(); i++)
  {
    delete i->second;
    i->second = nullptr;
  }
}

// Set shader
Shader* ShaderManager::SetShader(const char* path, Shader::Type type)
{
  Logger::LogTrace(Logger::Module::SHADER_MANAGER, "Shader* SetShader(const char* path, Shader::Type type)");

  std::string dir = "res/shaders/";
  std::ifstream file;

  switch (type)
  {
    // Graphics shader
    case Shader::Type::GRAPHICS:
    {
      std::string vsPath = dir + path + ".vert";
      std::string fsPath = dir + path + ".frag";
      Shader* shader = new Shader();

      if (shader->LoadGraphics(vsPath, fsPath))
      {
        ShaderManager::graphicsShaders.insert(std::pair<const char*, Shader*>(path, shader));
        return shader;
      }
      return nullptr;
    }

    // Geometry shader
    case Shader::Type::GEOMETRY:
    {
      std::string gsPath = dir + path + ".geom";
      Shader* shader = new Shader();

      if (shader->LoadGeometry(gsPath))
      {
        ShaderManager::geometryShaders.insert(std::pair<const char*, Shader*>(path, shader));
        return shader;
      }
      return nullptr;
    }

    // Compute shader
    case Shader::Type::COMPUTE:
    {
      std::string csPath = dir + path + ".comp";
      Shader* shader = new Shader();

      if (shader->LoadCompute(csPath))
      {
        ShaderManager::computeShaders.insert(std::pair<const char*, Shader*>(path, shader));
        return shader;
      }
      return nullptr;
    }

    // Default
    default:
      Logger::LogError(Logger::Module::SHADER_MANAGER, "Invalid shader type");
      return nullptr;
  }
}

// Get shader
Shader* ShaderManager::GetShader(const char* path, Shader::Type type)
{
  Logger::LogTrace(Logger::Module::SHADER_MANAGER, "Shader* GetShader(const char* path, Shader::Type type)");

  std::map<const char*, Shader*>::iterator it;

  switch (type)
  {
    // Graphics shader
    case Shader::Type::GRAPHICS:
    {
      it = ShaderManager::graphicsShaders.find(path);
      if (it != ShaderManager::graphicsShaders.end())
      {
        return (*it).second;
      }

      Logger::LogError(Logger::Module::SHADER_MANAGER, "Invalid shader path: %s", path);
      return nullptr;
    }

    // Geometry shader
    case Shader::Type::GEOMETRY:
    {
      it = ShaderManager::geometryShaders.find(path);
      if (it != ShaderManager::geometryShaders.end())
      {
        return (*it).second;
      }

      Logger::LogError(Logger::Module::SHADER_MANAGER, "Invalid shader path: %s", path);
      return nullptr;
    }

    // Compute shader
    case Shader::Type::COMPUTE:
    {
      it = ShaderManager::computeShaders.find(path);
      if (it != ShaderManager::computeShaders.end())
      {
        return (*it).second;
      }

      Logger::LogError(Logger::Module::SHADER_MANAGER, "Invalid shader path: %s", path);
      return nullptr;
    }

    // Default
    default:
      Logger::LogError(Logger::Module::SHADER_MANAGER, "Invalid shader path: %s", path);
      return nullptr;
  }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
