////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Engine.h"

// Constructor
Engine::Engine(const char* title, const int &width, const int &height)
{
  this->window = nullptr;
  this->title = title;
  this->width = width;
  this->height = height;
}

// Create engine
bool Engine::Create()
{
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
  this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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

  // Set event callbacks
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
    std::string sTitle = title + " | fps: " + fps + " ms: " + ms;
    glfwSetWindowTitle(this->window, sTitle.c_str());

    // Update event callback
    this->OnUpdate();

    // Clear window
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render event callback
    this->OnRender();

    // Swap buffers and poll events
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  // End event callback
  this->OnEnd();
  this->DisplayEndLog();

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
  glfwSetFramebufferSizeCallback(this->window, Engine::FramebufferSizeCallback);
}

// Display start log
void Engine::DisplayStartLog()
{
  std::cout << "\n====== Starting debug window ======\n" << std::endl;

  std::cout << "Application name: " << title << std::endl;
  std::cout << "Application version: " << "v0.1.0" << std::endl;
  std::cout << std::endl;

  const GLubyte *vendor = glGetString(GL_VENDOR);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "OpenGL company: " << vendor << std::endl;
  std::cout << "OpenGL renderer: " << renderer << std::endl;
  std::cout << "OpenGL version: " << version << std::endl;

  std::cout << "\n====== Rendering display window ======\n" << std::endl;
}

// Display end log
void Engine::DisplayEndLog()
{
  std::cout << "\n====== Closing display window ======\n" << std::endl;
  std::cout << "Application ended" << std::endl;
  std::cout << "\n====== Ending debug window ======\n" << std::endl;
}

// Get window
GLFWwindow &Engine::GetWindow()
{
  return *this->window;
}

// Get window size
glm::ivec2 Engine::GetWindowSize()
{
  glm::ivec2 size;
  glfwGetWindowSize(this->window, &size.x, &size.y);
  return size;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
