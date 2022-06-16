////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Prototypes
class Engine;

// Input class
class Input
{
  friend Engine;

  // Scroll enum
  enum class Scroll
  {
    Horizontal,
    Vertical
  };

  // Properties
  private:
    static glm::vec2 currentPosition;
    static glm::vec2 previousPosition;
    static glm::vec2 deltaPosition;
    static unsigned int buttonCurrentStates[GLFW_MOUSE_BUTTON_LAST];
    static unsigned int buttonPreviousStates[GLFW_MOUSE_BUTTON_LAST];
    static int scrollStates[2];
    static unsigned int keyCurrentStates[GLFW_KEY_LAST];
    static unsigned int keyPreviousStates[GLFW_KEY_LAST];

  // Methods: cursor
  public:
    static void SetCursorVisibility(const bool &visible);
    static bool IsCursorVisible();

  // Methods: callbacks
  protected:
    static void SetCallbacks(GLFWwindow* window);
    static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  // Methods: update
  protected:
    static void Update();

  // Getters
  public:
    static bool IsMouseDown(const int &button);
    static bool IsMousePressed(const int &button);
    static bool IsKeyDown(const int &key);
    static bool IsKeyPressed(const int &key);
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseDelta();
    static double GetMouseScroll(Input::Scroll direction);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
