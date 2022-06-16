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
  // Properties
  private:
    static Application* app;

  // Methods: events
  private:
    virtual void OnStart() override;
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    virtual void OnEnd() override;

  // Getters
  public:
    static Application &GetApp();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
