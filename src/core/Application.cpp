////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "Application.h"

// Set default values
Application *Application::app = nullptr;

// Start event callback
void Application::OnStart()
{
	Logger::LogTrace(ModuleData::Name::APPLICATION, "void OnStart()");

	// Link static pointer
	Application::app = this;

	// Remove default cursor
	Input::SetCursorVisibility(false);

	// Create world
	this->world = new World();
}

// Update event callback
void Application::OnUpdate()
{
	Logger::LogTrace(ModuleData::Name::APPLICATION, "void OnUpdate()");

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
	Logger::LogTrace(ModuleData::Name::APPLICATION, "void OnRender()");

	// Render world
	this->world->Render();

	// Render ImGui window
	if (this->world)
	{
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
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
}

// End event callback
void Application::OnEnd()
{
	Logger::LogTrace(ModuleData::Name::APPLICATION, "void OnEnd()");

	// Delete world
	delete this->world;
}

// Get application
Application &Application::GetApp()
{
	Logger::LogTrace(ModuleData::Name::APPLICATION, "Application &GetApp()");

	return *Application::app;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
