////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
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
  // Set values
  this->title = title;
  this->version = version;
  this->width = width;
  this->height = height;

  // Initialize GLFW
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
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
    std::cout << "Failed to create window or context" << std::endl;
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(this->window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
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
  // Start event callback
  this->DisplayStartLog();
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
  this->DisplayEndLog();

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
  glViewport(0, 0, width, height);
}

// Set event callbacks
void Engine::SetEventCallbacks()
{
  Input::SetCallbacks(this->window);
  glfwSetFramebufferSizeCallback(this->window, Engine::FramebufferSizeCallback);
}

// Display start log
void Engine::DisplayStartLog()
{
  std::cout << "\n\033[7m" << "====== Starting debug window ======" << "\033[0m\n" << std::endl;

  std::cout << "Application name: " << this->title << std::endl;
  std::cout << "Application version: " << this->version << std::endl;
  std::cout << std::endl;

  std::cout << "OpenGL company: " << this->GetGLVendor() << std::endl;
  std::cout << "OpenGL renderer: " << this->GetGLRenderer() << std::endl;
  std::cout << "OpenGL version: " << this->GetGLVersion() << std::endl;

  std::cout << "\n\033[7m" << "====== Rendering display window ======" << "\033[0m\n" << std::endl;
}

// Display end log
void Engine::DisplayEndLog()
{
  std::cout << "\n\033[7m" << "====== Closing display window ======" << "\033[0m\n" << std::endl;
  std::cout << "Application ended" << std::endl;
  std::cout << "\n\033[7m" << "====== Ending debug window ======" << "\033[0m\n" << std::endl;
}

// Get window
GLFWwindow &Engine::GetWindow()
{
  return *Engine::window;
}

// Get window size
glm::ivec2 Engine::GetWindowSize()
{
  glm::ivec2 size;
  glfwGetWindowSize(Engine::window, &size.x, &size.y);
  return size;
}

// Get OpenGL vendor string
std::string Engine::GetGLVendor()
{
  return std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
}

// Get OpenGL renderer string
std::string Engine::GetGLRenderer()
{
  return std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
}

// Get OpenGL version string
std::string Engine::GetGLVersion()
{
  return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
