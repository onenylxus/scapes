////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "ShaderManager.h"

// Set default values
std::map<const char*, Shader*> ShaderManager::graphicsShaders;
std::map<const char*, Shader*> ShaderManager::geometryShaders;
std::map<const char*, Shader*> ShaderManager::computeShaders;

// Init shaders
void ShaderManager::Init()
{
  ShaderManager::SetShader("base");
}

// Destroy shaders
void ShaderManager::Destroy()
{
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
  std::string dir = "../../res/shaders/";
  std::ifstream file;

  switch (type)
  {
    // Graphics shader
    case Shader::Type::GRAPHICS:
    {
      // Open vertex shader file
      file.open(dir + path + ".vert");

      // Check vertex shader file
      if (!file.is_open())
      {
        std::cout << "File failed to open: " << path << std::endl;
        file.close();
        return nullptr;
      }

      // Set vertex shader path
      std::string vsPath = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();

      // Open fragment shader file
      file.open(dir + path + ".frag");

      // Check fragment shader file
      if (!file.is_open())
      {
        std::cout << "File failed to open: " << path << std::endl;
        file.close();
        return nullptr;
      }

      // Set fragment shader path
      std::string fsPath = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();

      // Finalize shader
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
      // Open geometry shader file
      file.open(dir + path + ".geom");

      // Check geometry shader file
      if (!file.is_open())
      {
        std::cout << "File failed to open: " << path << std::endl;
        file.close();
        return nullptr;
      }

      // Set geometry shader path
      std::string gsPath = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();

      // Finalize shader
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
      // Open compute shader file
      file.open(dir + path + ".comp");

      // Check compute shader file
      if (!file.is_open())
      {
        std::cout << "File failed to open: " << path << std::endl;
        file.close();
        return nullptr;
      }

      // Set compute shader path
      std::string csPath = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();

      // Finalize shader
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
      std::cout << "Invalid shader type" << std::endl;
      return nullptr;
  }
}

// Get shader
Shader* ShaderManager::GetShader(const char* path, Shader::Type type)
{
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

      std::cout << "Invalid shader path: " << path << std::endl;
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

      std::cout << "Invalid shader path: " << path << std::endl;
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

      std::cout << "Invalid shader path: " << path << std::endl;
      return nullptr;
    }

    // Default
    default:
      std::cout << "Invalid shader type" << std::endl;
      return nullptr;
  }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
