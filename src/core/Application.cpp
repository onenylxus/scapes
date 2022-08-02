////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Application.h"

// Set default values
Application* Application::app = nullptr;

// Start event callback
void Application::OnStart()
{
  // Link static pointer
  Application::app = this;

  // Remove default cursor
  Input::SetCursorVisibility(false);

  // Create world
  this->world = new World();
  this->DisplayWorldStartLog();
}

// Update event callback
void Application::OnUpdate()
{
  // Debug
  if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
  {
    Input::SetCursorVisibility(!Input::IsCursorVisible());
  }

  // Update world
  this->world->Update();
}

// Render event callback
void Application::OnRender()
{
  // Render world
  this->world->Render();

  // Render OpenGL information through ImGui window
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("OpenGL Information", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
  ImGui::SetCursorPos(ImVec2(4.0f, 4.0f));
  ImGui::Text("%s %s", this->title.c_str(), this->version.c_str());
  ImGui::SetCursorPos(ImVec2(4.0f, 20.0f));
  ImGui::Text("OpenGL company: %s", this->GetGLVendor().c_str());
  ImGui::SetCursorPos(ImVec2(4.0f, 36.0f));
  ImGui::Text("OpenGL renderer: %s", this->GetGLRenderer().c_str());
  ImGui::SetCursorPos(ImVec2(4.0f, 52.0f));
  ImGui::Text("OpenGL version: %s", this->GetGLVersion().c_str());
  ImGui::End();
}

// End event callback
void Application::OnEnd()
{
  // Delete world
  delete this->world;
  this->DisplayWorldEndLog();
}

// Display world start log
void Application::DisplayWorldStartLog()
{
  Logger::LogInfo("Application", "World started", Logger::Color::YELLOW);
}

// Display world end log
void Application::DisplayWorldEndLog()
{
  Logger::LogInfo("Application", "World ended", Logger::Color::YELLOW);
}

// Get application
Application &Application::GetApp()
{
  return *Application::app;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
