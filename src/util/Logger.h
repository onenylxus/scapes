////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <mutex>
#include "Time.h"

// Logger class
class Logger
{
  // Priority enum
  public:
    enum class Priority
    {
      TRACE,
      DEBUG,
      INFO,
      WARN,
      ERROR
    };

  // Color enum
  public:
    enum class Color
    {
      BLACK = 30,
      RED,
      GREEN,
      YELLOW,
      BLUE,
      MAGENTA,
      CYAN,
      WHITE
    };

  // Module enum
  public:
    enum class Module
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
      CAMERA_2D,
      CAMERA_3D,
      CAMERA_PLAYER,
      BLOCK,
      CHUNK,
      ENTITY,
      WORLD,
      _MODULE_SIZE
    };

  // Priority data
  private:
    static inline const char* priorities[5] = {
      "Trace",
      "Debug",
      "Info",
      "Warn",
      "Error"
    };

  // Name data
  private:
    static inline const char* names[(int)Logger::Module::_MODULE_SIZE] = {
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
      "Camera2D",
      "Camera3D",
      "CameraPlayer",
      "Block",
      "Chunk",
      "Entity",
      "World"
    };

  // Color data
  private:
    static inline Logger::Color colors[(int)Logger::Module::_MODULE_SIZE] = {
      Logger::Color::BLACK,  // Logger
      Logger::Color::WHITE,  // Application
      Logger::Color::CYAN,   // Clock
      Logger::Color::WHITE,  // Engine
      Logger::Color::CYAN,   // Input
      Logger::Color::BLUE,   // AABB
      Logger::Color::BLUE,   // Camera
      Logger::Color::BLUE,   // Cubemap
      Logger::Color::BLUE,   // Object
      Logger::Color::BLUE,   // Shader
      Logger::Color::BLUE,   // Skybox
      Logger::Color::BLUE,   // Sprite
      Logger::Color::BLUE,   // Texture
      Logger::Color::BLUE,   // Tilemap
      Logger::Color::BLUE,   // Transform
      Logger::Color::RED,    // BlockManager
      Logger::Color::RED,    // ChunkManager
      Logger::Color::RED,    // EntityManager
      Logger::Color::RED,    // ShaderManager
      Logger::Color::YELLOW, // Camera2D
      Logger::Color::YELLOW, // Camera3D
      Logger::Color::YELLOW, // CameraPlayer
      Logger::Color::GREEN,  // Block
      Logger::Color::GREEN,  // Chunk
      Logger::Color::GREEN,  // Entity
      Logger::Color::GREEN   // World
    };

  // Properties
  private:
    static inline Logger::Priority priority = Logger::Priority::DEBUG;
    static inline std::mutex mutex;
    static inline const char* path = 0;
    static inline FILE* file = 0;
    static inline bool isWriteEnabled = false;

  // Methods
  public:
    static void EnableWrite(const char* path)
    {
      // Close file
      DisableWrite();

      // Open file from path
      Logger::isWriteEnabled = false;
      Logger::path = path;
      Logger::file = fopen(Logger::path, "a");

      // Check file
      if (Logger::file == 0)
      {
        Logger::LogError(Logger::Module::LOGGER, "File failed to open: %s", Logger::path);
        return;
      }
      Logger::isWriteEnabled = true;
    }

    static void DisableWrite()
    {
      fclose(Logger::file);
      Logger::file = 0;
      Logger::isWriteEnabled = false;
    }

    template<typename... Args>
    static void LogTrace(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::TRACE)
      {
        Logger::LogPriority(module, Logger::Priority::TRACE, message, args...);
      }
    }

    template<typename... Args>
    static void LogDebug(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::DEBUG)
      {
        Logger::LogPriority(module, Logger::Priority::DEBUG, message, args...);
      }
    }

    template<typename... Args>
    static void LogInfo(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::INFO)
      {
        Logger::LogPriority(module, Logger::Priority::INFO, message, args...);
      }
    }

    template<typename... Args>
    static void LogWarn(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::WARN)
      {
        Logger::LogPriority(module, Logger::Priority::WARN, message, args...);
      }
    }

    template<typename... Args>
    static void LogError(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::ERROR)
      {
        Logger::LogPriority(module, Logger::Priority::ERROR, message, args...);
      }
    }

    template<typename... Args>
    static void Log(const char* message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, true, message, args...);
    }

    template<typename... Args>
    static void Log(Logger::Color color, const char* message, Args... args)
    {
      Logger::Log(color, true, message, args...);
    }

    template<typename... Args>
    static void Log(bool timestamp, const char* message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, timestamp, message, args...);
    }

    template<typename... Args>
    static void Log(Logger::Color color, bool timestamp, const char* message, Args... args)
    {
      // Lock mutex within scope
      std::scoped_lock lock(Logger::mutex);

      // Timestamp
      if (timestamp)
      {
        std::printf("\033[%i;1m", color);
        Time::Print();
        std::printf(" ");
      }

      // Message
      std::printf("\033[0m\033[%im", color);
      std::printf(message, args...);
      std::printf("\033[0m\n");
    }

  private:
    template<typename... Args>
    static void LogPriority(Logger::Module module, Logger::Priority priority, const char* message, Args... args)
    {
      // Exclude module size option
      if (module == Logger::Module::_MODULE_SIZE)
      {
        return;
      }

      // Setup variables
      int index = (int)module;

      // Lock mutex within scope
      std::scoped_lock lock(Logger::mutex);

      // Timestamp
      std::printf("\033[%i;1m", Logger::colors[index]);
      Time::Print();
      if (Logger::isWriteEnabled)
      {
        Time::FilePrint(Logger::file);
      }

      // Class name
      std::printf(" \033[7m %s ", Logger::names[index]);
      if (Logger::isWriteEnabled)
      {
        std::fprintf(Logger::file, " %s |", Logger::names[index]);
      }

      // Priority
      std::printf("\033[0m \033[%im[%s] ", Logger::colors[index], Logger::priorities[(int)priority]);
      if (Logger::isWriteEnabled)
      {
        std::fprintf(Logger::file, " %s] ", Logger::priorities[(int)priority]);
      }

      // Message
      std::printf(message, args...);
      std::printf("\033[0m\n");
      if (Logger::isWriteEnabled)
      {
        std::fprintf(Logger::file, message, args...);
        std::fprintf(Logger::file, "\n");
      }
    }

  // Setters
  public:
    static void SetPriority(Logger::Priority value)
    {
      Logger::priority = value;
    }
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
