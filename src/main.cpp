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
  // Set logger priority level
  Logger::SetPriority(Logger::Priority::DEBUG);

  // Create application
  Application* app = new Application();
  if (app->Create(title, version, width, height))
  {
    app->Start();
  }

  // Return
  return 0;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
