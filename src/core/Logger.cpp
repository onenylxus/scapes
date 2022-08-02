////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Logger.h"

// Set default values
Logger::Priority Logger::priority = Logger::Priority::TRACE;
std::mutex Logger::mutex;

// Log with trace priority
void Logger::LogTrace(const char* name, const char* message, Logger::Color color)
{
  if (Logger::priority <= Logger::Priority::TRACE)
  {
    Logger::Log(name, message, color);
  }
}

// Log with debug priority
void Logger::LogDebug(const char* name, const char* message, Logger::Color color)
{
  if (Logger::priority <= Logger::Priority::DEBUG)
  {
    Logger::Log(name, message, color);
  }
}

// Log with info priority
void Logger::LogInfo(const char* name, const char* message, Logger::Color color)
{
  if (Logger::priority <= Logger::Priority::INFO)
  {
    Logger::Log(name, message, color);
  }
}

// Log with warn priority
void Logger::LogWarn(const char* name, const char* message, Logger::Color color)
{
  if (Logger::priority <= Logger::Priority::WARN)
  {
    Logger::Log(name, message, color);
  }
}

// Log with error priority
void Logger::LogError(const char* name, const char* message, Logger::Color color)
{
  if (Logger::priority <= Logger::Priority::ERROR)
  {
    Logger::Log(name, message, color);
  }
}

// Regular log
void Logger::Log(const char* name, const char* message, Logger::Color color)
{
  // Setup variables
  std::ostringstream os;
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
  os << Logger::ColorToAttr(color) << "\033[1m" << str;

  // Class name
  if (name[0] != '\0')
  {
    os << "\033[7m " << name << " ";
  }

  // Message
  os << "\033[0m " << Logger::ColorToAttr(color) << message << "\033[0m";
  std::cout << os.str() << std::endl;
}

// Convert color enum to attribute string
const char* Logger::ColorToAttr(Logger::Color color)
{
  std::ostringstream os;
  os << "\033[" << (int)color << "m";
  return os.str().c_str();
}

// Set priority level
void Logger::SetPriority(Logger::Priority value)
{
  Logger::priority = value;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
