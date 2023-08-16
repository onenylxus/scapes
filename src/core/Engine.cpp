////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Engine.h"

// Set default values
GLFWwindow* Engine::window = nullptr;
std::string Engine::title;
std::string Engine::version;
int Engine::width;
int Engine::height;

// Create engine
bool Engine::Create(const char* title, const char* version, const int &width, const int &height)
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "bool Create(const char* title, const char* version, const int &width, const int &height)");

  // Set values
  this->title = title;
  this->version = version;
  this->width = width;
  this->height = height;

  // Initialize GLFW
  if (!glfwInit())
  {
    Logger::LogError(ModuleData::Name::ENGINE, "Failed to initialize GLFW");
    return false;
  }

  // Configure GLFW (using OpenGL 4.5, modern functions only)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // Create window
  this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
  if (!this->window)
  {
    Logger::LogError(ModuleData::Name::ENGINE, "Failed to create window or context");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(this->window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    Logger::LogError(ModuleData::Name::ENGINE, "Failed to initialize GLAD");
    glfwTerminate();
    return false;
  }

  // Initialize ImGui
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(this->window, true);
  ImGui_ImplOpenGL3_Init("#version 450");
  ImGui::StyleColorsDark();

  // Set event callbacks
  glViewport(0, 0, width, height);
  this->SetEventCallbacks();
  return true;
}

// Start engine
void Engine::Start()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "void Start()");

  // Start event callback
  Logger::Log(Logger::Color::BLACK, false, "\n===============================");
  Logger::Log(Logger::Color::BLACK, false, "Application name: %s", this->title.c_str());
  Logger::Log(Logger::Color::BLACK, false, "Application version: %s", this->version.c_str());
  Logger::Log(Logger::Color::BLACK, false, "OpenGL company: %s", this->GetGLVendor().c_str());
  Logger::Log(Logger::Color::BLACK, false, "OpenGL renderer: %s", this->GetGLRenderer().c_str());
  Logger::Log(Logger::Color::BLACK, false, "OpenGL version: %s", this->GetGLVersion().c_str());
  Logger::Log(Logger::Color::BLACK, false, "===============================\n");
  Logger::LogInfo(ModuleData::Name::ENGINE, "Application started");
  this->OnStart();

  // Run engine loop
  while (!glfwWindowShouldClose(this->window))
  {
    // Update clock
    Clock::Update();
    std::string fps = std::to_string(1.0f / Clock::GetDelta());
    std::string ms = std::to_string(Clock::GetDelta());
    std::string sTitle = this->title + " | fps: " + fps + " ms: " + ms;
    glfwSetWindowTitle(this->window, sTitle.c_str());

    // Create new ImGui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Update event callback
    this->OnUpdate();

    // Update input
    Input::Update();

    // Clear window
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render event callback
    this->OnRender();

    // Render ImGui frames
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers and poll events
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  // End event callback
  this->OnEnd();
  Logger::LogInfo(ModuleData::Name::ENGINE, "Application ended");

  // Terminate ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Terminate GLFW
  glfwTerminate();
}

// Frame buffer size callback
void Engine::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "void FramebufferSizeCallback(GLFWwindow* window, int width, int height)");

  glViewport(0, 0, width, height);
}

// Set event callbacks
void Engine::SetEventCallbacks()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "void SetEventCallbacks()");

  Input::SetCallbacks(this->window);
  glfwSetFramebufferSizeCallback(this->window, Engine::FramebufferSizeCallback);
}

// Get window
GLFWwindow &Engine::GetWindow()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "GLFWwindow &GetWindow()");

  return *Engine::window;
}

// Get window size
glm::ivec2 Engine::GetWindowSize()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "glm::ivec2 GetWindowSize()");

  glm::ivec2 size;
  glfwGetWindowSize(Engine::window, &size.x, &size.y);
  return size;
}

// Get OpenGL vendor string
std::string Engine::GetGLVendor()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "std::string GetGLVendor()");

  return std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
}

// Get OpenGL renderer string
std::string Engine::GetGLRenderer()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "std::string GetGLRenderer()");

  return std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
}

// Get OpenGL version string
std::string Engine::GetGLVersion()
{
  Logger::LogTrace(ModuleData::Name::ENGINE, "std::string GetGLVersion()");

  return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
