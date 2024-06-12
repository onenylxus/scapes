////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2024 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Input.h"

// Set default values
glm::vec2 Input::currentPosition;
glm::vec2 Input::previousPosition;
glm::vec2 Input::deltaPosition;
unsigned int Input::buttonCurrentStates[GLFW_MOUSE_BUTTON_LAST];
unsigned int Input::buttonPreviousStates[GLFW_MOUSE_BUTTON_LAST];
int Input::scrollStates[2];
unsigned int Input::keyCurrentStates[GLFW_KEY_LAST];
unsigned int Input::keyPreviousStates[GLFW_KEY_LAST];

// Mouse position callback
void Input::MousePositionCallback(GLFWwindow *window, double xpos, double ypos)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void MousePositionCallback(GLFWwindow *window, double xpos, double ypos)");

  Input::previousPosition = Input::currentPosition;
  Input::currentPosition = glm::vec2(xpos, ypos);
  Input::deltaPosition = Input::currentPosition - Input::previousPosition;
}

// Mouse button callback
void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)");

  if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
  {
    Input::buttonCurrentStates[button] = action;
  }
}

// Mouse scroll callback
void Input::MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)");

  Input::scrollStates[0] += xoffset;
  Input::scrollStates[1] += yoffset;
}

// Key callback
void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)");

  if (key >= 0 && key < GLFW_KEY_LAST)
  {
    Input::keyCurrentStates[key] = action;
  }
}

// Update function
void Input::Update()
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void Update()");

  Input::deltaPosition = glm::vec2(0.0f);
  Input::scrollStates[0] = 0;
  Input::scrollStates[1] = 0;

  for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
  {
    Input::buttonPreviousStates[i] = Input::buttonCurrentStates[i];
  }

  for (int i = 0; i < GLFW_KEY_LAST; i++)
  {
    Input::keyPreviousStates[i] = Input::keyCurrentStates[i];
  }
}

// Set cursor visibility
void Input::SetCursorVisibility(const bool& visible)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void SetCursorVisibility(const bool& visible)");

  if (visible)
  {
    glfwSetInputMode(&Engine::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glm::vec2 size = Engine::GetWindowSize() / 2;
    glfwSetCursorPos(&Engine::GetWindow(), size.x, size.y);
    Input::currentPosition = size;
  }
  else
  {
    glfwSetInputMode(&Engine::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  Logger::LogDebug(ModuleData::Name::INPUT, "Cursor visibility set to %s", visible ? "true" : "false");
}

// Set callbacks
void Input::SetCallbacks(GLFWwindow* window)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "void SetCallbacks(GLFWwindow* window)");

  glfwSetCursorPosCallback(window, Input::MousePositionCallback);
  glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
  glfwSetScrollCallback(window, Input::MouseScrollCallback);
  glfwSetKeyCallback(window, Input::KeyCallback);
}

// Get cursor visibility
bool Input::IsCursorVisible()
{
  Logger::LogTrace(ModuleData::Name::INPUT, "bool IsCursorVisible()");

  return glfwGetInputMode(&Engine::GetWindow(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}

// Check if mouse is down
bool Input::IsMouseDown(const int &button)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "bool IsMouseDown(const int &button)");

  if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
  {
    return Input::buttonCurrentStates[button] == GLFW_PRESS || Input::buttonCurrentStates[button] == GLFW_REPEAT;
  }

  return false;
}

// Check if mouse is pressed
bool Input::IsMousePressed(const int &button)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "bool IsMousePressed(const int &button)");

  if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
  {
    return Input::buttonCurrentStates[button] == GLFW_PRESS && Input::buttonPreviousStates[button] == GLFW_RELEASE;
  }

  return false;
}

// Check if key is down
bool Input::IsKeyDown(const int &key)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "bool IsKeyDown(const int &key)");

  if (key >= 0 && key < GLFW_KEY_LAST)
  {
    return Input::keyCurrentStates[key] == GLFW_PRESS || Input::keyCurrentStates[key] == GLFW_REPEAT;
  }

  return false;
}

// Check if key is pressed
bool Input::IsKeyPressed(const int &key)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "bool IsKeyPressed(const int &key)");

  if (key >= 0 && key < GLFW_KEY_LAST)
  {
    return Input::keyCurrentStates[key] == GLFW_PRESS && Input::keyPreviousStates[key] == GLFW_RELEASE;
  }

  return false;
}

// Get mouse position
glm::vec2 Input::GetMousePosition()
{
  Logger::LogTrace(ModuleData::Name::INPUT, "glm::vec2 GetMousePosition()");

  return Input::currentPosition;
}

// Get mouse delta
glm::vec2 Input::GetMouseDelta()
{
  Logger::LogTrace(ModuleData::Name::INPUT, "glm::vec2 GetMouseDelta()");

  return Input::deltaPosition;
}

// Get mouse scroll
double Input::GetMouseScroll(Input::Scroll direction)
{
  Logger::LogTrace(ModuleData::Name::INPUT, "double GetMouseScroll(Input::Scroll direction)");

  return Input::scrollStates[(int)direction];
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
