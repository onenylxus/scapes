////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../util/Logger.h"

// Clock class
class Clock
{
  // Properties
  private:
    static float then;
    static float delta;
    static float total;

  // Methods
  public:
    static void Update();

  // Getters
  public:
    static float GetDelta();
    static float GetTotal();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
