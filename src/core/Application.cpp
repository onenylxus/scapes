////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Application.h"

// Set default values
Application* Application::app;

// Start event callback
void Application::OnStart()
{
  // Link static pointer
  Application::app = this;

  // Remove default cursor
  Input::SetCursorVisibility(false);
}

// Update event callback
void Application::OnUpdate()
{
  // Debug
  if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
  {
    Input::SetCursorVisibility(!Input::IsCursorVisible());
  }
}

// Render event callback
void Application::OnRender()
{

}

// End event callback
void Application::OnEnd()
{

}

// Get application
Application &Application::GetApp()
{
  return *Application::app;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
