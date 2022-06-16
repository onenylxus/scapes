////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "Engine.h"

// Application class
class Application : public Engine
{
  // Constructor and destructor
  public:
    Application(const char* title, const int &width, const int &height);
    virtual ~Application() = default;

  // Methods: events
  private:
    virtual void OnStart() override;
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    virtual void OnEnd() override;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
