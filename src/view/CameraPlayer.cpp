////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "CameraPlayer.h"

// Constructor
CameraPlayer::CameraPlayer(Entity& entity, const glm::vec3& position) : Camera3D(position)
{
  Logger::LogTrace(ModuleData::Name::CAMERA_PLAYER, "CameraPlayer::CameraPlayer(Entity& entity, const glm::vec3& position)");

  this->entity = &entity;
}

// Destructor
CameraPlayer::~CameraPlayer()
{
  Logger::LogTrace(ModuleData::Name::CAMERA_PLAYER, "CameraPlayer::~CameraPlayer()");
}

// Update camera
void CameraPlayer::Update()
{
  Logger::LogTrace(ModuleData::Name::CAMERA_PLAYER, "void CameraPlayer::Update()");

  if (!Input::IsCursorVisible())
  {
    glm::vec2 delta = Input::GetMouseDelta() * 0.3f;
    this->RotateBy(delta.x, delta.y);

    if (this->pitch > 89.0f)
    {
      this->pitch = 89.0f;
    }
    else if (this->pitch < -89.0f)
    {
      this->pitch = -89.0f;
    }

    this->position = this->entity->GetPosition();
    this->UpdateCamera();
  }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
