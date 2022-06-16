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
#include "Input.h"

// Engine class
class Engine
{
  // Properties
  protected:
    static GLFWwindow* window;
    static std::string title;
    static int width;
    static int height;

  // Methods: initialization
  public:
    bool Create(const char* title, const int &width, const int &height);
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
    static GLFWwindow &GetWindow();
    static std::string GetTitle();
    static glm::ivec2 GetWindowSize();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
