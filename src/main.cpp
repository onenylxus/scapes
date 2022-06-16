////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "./core/Application.h"

// Application values
const char* title = "Scapes";
const int width = 1280;
const int height = 720;

// Main function
int main(int argc, char* argv[])
{
  // Create application
  Application* app = new Application();
  if (app->Create(title, width, height))
  {
    app->Start();
  }

  // Return
  return 0;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
