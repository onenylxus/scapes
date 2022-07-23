////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Clock.h"
#include "Input.h"

// Engine class
class Engine
{
  // Properties
  protected:
    static GLFWwindow* window;
    static std::string title;
    static std::string version;
    static int width;
    static int height;

  // Methods
  public:
    bool Create(const char* title, const char* version, const int &width, const int &height);
    void Start();

  protected:
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    virtual void OnEnd() = 0;

  private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void SetEventCallbacks();

  private:
    void DisplayStartLog();
    void DisplayEndLog();

  // Getters
  public:
    static GLFWwindow &GetWindow();
    static glm::ivec2 GetWindowSize();
    static std::string GetGLVendor();
    static std::string GetGLRenderer();
    static std::string GetGLVersion();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
