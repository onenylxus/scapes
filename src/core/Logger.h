////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

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

  // Properties
  private:
    static Logger::Priority priority;
    static std::mutex mutex;

  // Methods
  public:
    static void LogTrace(const char* name, const char* message, Logger::Color color);
    static void LogDebug(const char* name, const char* message, Logger::Color color);
    static void LogInfo(const char* name, const char* message, Logger::Color color);
    static void LogWarn(const char* name, const char* message, Logger::Color color);
    static void LogError(const char* name, const char* message, Logger::Color color);
    static void Log(const char* name, const char* message, Logger::Color color);

  private:
    static const char* ColorToAttr(Logger::Color color);

  // Setters
  public:
    static void SetPriority(Logger::Priority value);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
