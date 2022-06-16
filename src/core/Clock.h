////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Clock class
class Clock
{
  // Properties
  private:
    static float then;
    static float delta;
    static float total;

  // Methods: update
  public:
    static void Update();

  // Getters
  public:
    static float GetDelta();
    static float GetTotal();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
