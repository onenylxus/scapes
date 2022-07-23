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

}

// Get application
Application &Application::GetApp()
{
  return *Application::app;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
