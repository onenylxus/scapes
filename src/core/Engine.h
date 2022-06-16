////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include "Clock.h"

// Engine class
class Engine
{
  // Constructor and destructor
  protected:
    Engine(const char* title, const int &width, const int &height);
    virtual ~Engine() = default;

  // Properties
  protected:
    GLFWwindow* window;
    std::string title;
    int width;
    int height;

  // Methods: initialization
  public:
    bool Create();
    void Start();

  // Methods: events
  protected:
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    virtual void OnEnd() = 0;

  // Methods: callbacks
  private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void SetEventCallbacks();

  // Methods: logs
  private:
    void DisplayStartLog();
    void DisplayEndLog();

  // Getters
  public:
    GLFWwindow &GetWindow();
    glm::ivec2 GetWindowSize();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
