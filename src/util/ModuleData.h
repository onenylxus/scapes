////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once

// Prototypes
class Logger;

// Module data class
class ModuleData
{
  public:
    friend class Logger;

  // Name enum
  public:
    enum class Name
    {
      LOGGER,
      APPLICATION,
      CLOCK,
      ENGINE,
      INPUT,
      AABB,
      CAMERA,
      CUBEMAP,
      OBJECT,
      SHADER,
      SKYBOX,
      SPRITE,
      TEXTURE,
      TILEMAP,
      TRANSFORM,
      BLOCK_MANAGER,
      CHUNK_MANAGER,
      ENTITY_MANAGER,
      SHADER_MANAGER,
      RAYCAST,
      CAMERA_2D,
      CAMERA_3D,
      CAMERA_PLAYER,
      RENDERER,
      BLOCK,
      CHUNK,
      ENTITY,
      WORLD,
      _MODULE_SIZE
    };

  // Type enum
  private:
    enum class Type
    {
      LOGGER,
      CORE_PRIMARY,
      CORE_SECONDARY,
      GL,
      MANAGER,
      PLAYER,
      VIEW,
      WORLD,
      _TYPE_SIZE
    };

  // Name data
  private:
    static inline const char* names[(int)ModuleData::Name::_MODULE_SIZE] = {
      "Logger",
      "Application",
      "Clock",
      "Engine",
      "Input",
      "AABB",
      "Camera",
      "Cubemap",
      "Object",
      "Shader",
      "Skybox",
      "Sprite",
      "Texture",
      "Tilemap",
      "Transform",
      "BlockManager",
      "ChunkManager",
      "EntityManager",
      "ShaderManager",
      "Raycast",
      "Camera2D",
      "Camera3D",
      "CameraPlayer",
      "Renderer",
      "Block",
      "Chunk",
      "Entity",
      "World"
    };

  // Type data
  private:
    static inline ModuleData::Type types[(int)ModuleData::Name::_MODULE_SIZE] = {
      ModuleData::Type::LOGGER,         // Logger
      ModuleData::Type::CORE_PRIMARY,   // Application
      ModuleData::Type::CORE_SECONDARY, // Clock
      ModuleData::Type::CORE_PRIMARY,   // Engine
      ModuleData::Type::CORE_SECONDARY, // Input
      ModuleData::Type::GL,             // AABB
      ModuleData::Type::GL,             // Camera
      ModuleData::Type::GL,             // Cubemap
      ModuleData::Type::GL,             // Object
      ModuleData::Type::GL,             // Shader
      ModuleData::Type::GL,             // Skybox
      ModuleData::Type::GL,             // Sprite
      ModuleData::Type::GL,             // Texture
      ModuleData::Type::GL,             // Tilemap
      ModuleData::Type::GL,             // Transform
      ModuleData::Type::MANAGER,        // BlockManager
      ModuleData::Type::MANAGER,        // ChunkManager
      ModuleData::Type::MANAGER,        // EntityManager
      ModuleData::Type::MANAGER,        // ShaderManager
      ModuleData::Type::PLAYER,         // Raycast
      ModuleData::Type::VIEW,           // Camera2D
      ModuleData::Type::VIEW,           // Camera3D
      ModuleData::Type::VIEW,           // CameraPlayer
      ModuleData::Type::VIEW,           // Renderer
      ModuleData::Type::WORLD,          // Block
      ModuleData::Type::WORLD,          // Chunk
      ModuleData::Type::WORLD,          // Entity
      ModuleData::Type::WORLD           // World
    };
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
