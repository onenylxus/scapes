////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <mutex>
#include "ModuleData.h"
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

  // Priority data
  private:
    static inline const char *priorities[5] = {
      "Trace",
      "Debug",
      "Info",
      "Warn",
      "Error"
    };

  // Color data
  private:
    static inline Logger::Color colors[(int)ModuleData::Type::_TYPE_SIZE] = {
      Logger::Color::BLACK,   // Logger
      Logger::Color::WHITE,   // Core (Primary)
      Logger::Color::CYAN,    // Core (Secondary)
      Logger::Color::BLUE,    // GL
      Logger::Color::RED,     // Manager
      Logger::Color::MAGENTA, // Player
      Logger::Color::YELLOW,  // View
      Logger::Color::GREEN    // World
    };

  // Properties
  private:
    static inline Logger::Priority priority = Logger::Priority::DEBUG;
    static inline std::mutex mutex;
    static inline const char *path = 0;
    static inline FILE *file = 0;
    static inline bool isWriteEnabled = false;

  // Methods
  public:
    static void EnableWrite(const char *path)
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
        Logger::LogError(ModuleData::Name::LOGGER, "File failed to open: %s", Logger::path);
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
    static void LogTrace(ModuleData::Name module, const char *message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::TRACE)
      {
        Logger::LogPriority(module, Logger::Priority::TRACE, message, args...);
      }
    }

    template<typename... Args>
    static void LogDebug(ModuleData::Name module, const char *message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::DEBUG)
      {
        Logger::LogPriority(module, Logger::Priority::DEBUG, message, args...);
      }
    }

    template<typename... Args>
    static void LogInfo(ModuleData::Name module, const char *message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::INFO)
      {
        Logger::LogPriority(module, Logger::Priority::INFO, message, args...);
      }
    }

    template<typename... Args>
    static void LogWarn(ModuleData::Name module, const char *message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::WARN)
      {
        Logger::LogPriority(module, Logger::Priority::WARN, message, args...);
      }
    }

    template<typename... Args>
    static void LogError(ModuleData::Name module, const char *message, Args... args)
    {
      if (Logger::priority <= Logger::Priority::ERROR)
      {
        Logger::LogPriority(module, Logger::Priority::ERROR, message, args...);
      }
    }

    template<typename... Args>
    static void Log(const char *message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, true, message, args...);
    }

    template<typename... Args>
    static void Log(Logger::Color color, const char *message, Args... args)
    {
      Logger::Log(color, true, message, args...);
    }

    template<typename... Args>
    static void Log(bool timestamp, const char *message, Args... args)
    {
      Logger::Log(Logger::Color::WHITE, timestamp, message, args...);
    }

    template<typename... Args>
    static void Log(Logger::Color color, bool timestamp, const char *message, Args... args)
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
    static void LogPriority(ModuleData::Name module, Logger::Priority priority, const char *message, Args... args)
    {
      // Exclude module size option
      if (module == ModuleData::Name::_MODULE_SIZE)
      {
        return;
      }

      // Setup variables
      int index = (int)module;
      int type = (int)ModuleData::types[index];

      // Lock mutex within scope
      std::scoped_lock lock(Logger::mutex);

      // Timestamp
      std::printf("\033[%i;1m", Logger::colors[type]);
      Time::Print();
      if (Logger::isWriteEnabled)
      {
        Time::FilePrint(Logger::file);
      }

      // Class name
      std::printf(" \033[7m %s ", ModuleData::names[index]);
      if (Logger::isWriteEnabled)
      {
        std::fprintf(Logger::file, " %s |", ModuleData::names[index]);
      }

      // Priority
      std::printf("\033[0m \033[%im[%s] ", Logger::colors[type], Logger::priorities[(int)priority]);
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
