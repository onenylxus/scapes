////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Clock.h"

// Set default values
float Clock::then = 0.0f;
float Clock::delta = 0.0f;
float Clock::total = 0.0f;

// Update clock
void Clock::Update()
{
	Logger::LogTrace(ModuleData::Name::CLOCK, "void Update()");

	Clock::delta = glfwGetTime() - Clock::then;
	Clock::then = glfwGetTime();
	Clock::total += Clock::delta;
}

// Get delta time
float Clock::GetDelta()
{
	Logger::LogTrace(ModuleData::Name::CLOCK, "float GetDelta()");

	return Clock::delta;
}

// Get total time
float Clock::GetTotal()
{
	Logger::LogTrace(ModuleData::Name::CLOCK, "float GetTotal()");

	return Clock::total;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
