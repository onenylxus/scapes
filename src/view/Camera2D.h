////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include "../gl/Camera.h"

// 2D camera class
class Camera2D : public Camera
{
	// Constructor and destructor
public:
	Camera2D(const glm::vec3 &position, const glm::vec3 &front, const float &left, const float &right, const float &top, const float &bottom);
	virtual ~Camera2D();

	// Properties
private:
	float left;
	float right;
	float top;
	float bottom;

	// Methods
private:
	virtual void UpdateCamera() override;
	virtual glm::mat4 CreateProjection() const override;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
