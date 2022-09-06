////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <ctime>
#include <mutex>
#include <stdio.h>

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
      ENTITY_MANAGER,
      SHADER_MANAGER,
      CAMERA_2D,
      CAMERA_3D,
      CAMERA_PLAYER,
      BLOCK,
      ENTITY,
      WORLD,
      _MODULE_SIZE
    };

  // Properties
  private:
    static inline const char* levels[5] = {
      "Trace",
      "Debug",
      "Info",
      "Warn",
      "Error"
    };
    static inline const char* names[(int)Logger::Module::_MODULE_SIZE] = {
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
      "EntityManager",
      "ShaderManager",
      "Camera2D",
      "Camera3D",
      "CameraPlayer",
      "Block",
      "Entity",
      "World"
    };
    static inline Logger::Color colors[(int)Logger::Module::_MODULE_SIZE] = {
      Logger::Color::WHITE,
      Logger::Color::CYAN,
      Logger::Color::WHITE,
      Logger::Color::CYAN,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::BLUE,
      Logger::Color::RED,
      Logger::Color::RED,
      Logger::Color::RED,
      Logger::Color::YELLOW,
      Logger::Color::YELLOW,
      Logger::Color::YELLOW,
      Logger::Color::GREEN,
      Logger::Color::GREEN,
      Logger::Color::GREEN
    };
    static inline Logger::Priority priority;
    static inline std::mutex mutex;

  // Methods
  public:
    template<typename... Args> static void LogTrace(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::TRACE)
      {
        Logger::LogPriority(module, Logger::Priority::TRACE, message, args...);
      }
    }

    template<typename... Args> static void LogDebug(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::DEBUG)
      {
        Logger::LogPriority(module, Logger::Priority::DEBUG, message, args...);
      }
    }

    template<typename... Args> static void LogInfo(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::INFO)
      {
        Logger::LogPriority(module, Logger::Priority::INFO, message, args...);
      }
    }

    template<typename... Args> static void LogWarn(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::WARN)
      {
        Logger::LogPriority(module, Logger::Priority::WARN, message, args...);
      }
    }

    template<typename... Args> static void LogError(Logger::Module module, const char* message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::ERROR)
      {
        Logger::LogPriority(module, Logger::Priority::ERROR, message, args...);
      }
    }

    template<typename... Args> static void Log(const char* message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, true, message, args...);
    }

    template<typename... Args> static void Log(Logger::Color color, const char* message, Args... args)
    {
      Logger::Log(color, true, message, args...);
    }

    template<typename... Args> static void Log(bool timestamp, const char* message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, timestamp, message, args...);
    }

    template<typename... Args> static void Log(Logger::Color color, bool timestamp, const char* message, Args... args)
    {
      // Lock mutex within scope
      std::scoped_lock lock(Logger::mutex);

      // Setup variables
      if (timestamp)
      {
        time_t now;
        tm* tm;
        char buf[100];
        const char* str = buf;

        // Timestamp
        std::time(&now);
        tm = std::localtime(&now);
        std::strftime(buf, 50, "[%Y-%m-%d %H:%M:%S] ", tm);
        std::printf("\033[%i;1m%s", color, str);
      }

      // Message
      std::printf("\033[0m\033[%im", color);
      std::printf(message, args...);
      std::printf("\033[0m\n");
    }

  private:
    template<typename... Args> static void LogPriority(Logger::Module module, Logger::Priority priority, const char* message, Args... args)
    {
      // Exclude module size option
      if (module == Logger::Module::_MODULE_SIZE)
      {
        return;
      }

      // Setup variables
      int index = (int)module;
      time_t now;
      tm* tm;
      char buf[100];
      const char* str = buf;

      // Lock mutex within scope
      std::scoped_lock lock(Logger::mutex);

      // Timestamp
      std::time(&now);
      tm = std::localtime(&now);
      std::strftime(buf, 50, "[%Y-%m-%d %H:%M:%S] ", tm);
      std::printf("\033[%i;1m%s", Logger::colors[index], str);

      // Class name
      std::printf("\033[7m %s ", Logger::names[index]);

      // Priority
      std::printf("\033[0m \033[%im", Logger::colors[index]);
      std::printf("%s: ", Logger::levels[(int)priority]);

      // Message
      std::printf(message, args...);
      std::printf("\033[0m\n");
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
