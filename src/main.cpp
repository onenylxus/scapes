////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "./core/Application.h"
#include "./util/Logger.h"

// Application values
const char* title = "Scapes";
const char* version = "v0.1.0";
const int width = 1280;
const int height = 720;

// Main function
int main(int argc, char* argv[])
{
  // Enable logger file write
  time_t t = time(0);
  struct tm* now = std::localtime(&t);
  char buffer[80];
  strftime(buffer, 80, "log/%Y%m%d_%H%M%S.txt", now);
  Logger::EnableWrite(buffer);

  // Create application
  Application* app = new Application();
  if (app->Create(title, version, width, height))
  {
    app->Start();
  }

  // Disable logger file write
  Logger::DisableWrite();

  // Return
  return 0;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
