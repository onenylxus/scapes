////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "Camera.h"

// Constructor
Camera::Camera(const glm::vec3 &position, const float &fov, const float &near, const float &far)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "Camera(const glm::vec3 &position, const float &fov, const float &near, const float &far)");

	this->position = position;
	this->up = glm::vec3(0, 1, 0);
	this->front = glm::vec3(0);
	this->right = glm::vec3(0);
	this->top = glm::vec3(0);
	this->fov = glm::radians(fov);
	this->near = near;
	this->far = far;
	this->yaw = -90.0f;
	this->pitch = 0;
	this->view = glm::mat4(0);
	this->projection = glm::mat4(0);
	this->SetDirty(true);
}

// Destructor
Camera::~Camera()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "~Camera()");
}

// Move camera
void Camera::MoveBy(const glm::vec3 &position)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void MoveBy(const glm::vec3 &position)");

	this->position += position;
	this->SetDirty(true);
}

// Rotate camera
void Camera::RotateBy(const float &yaw, const float &pitch)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void RotateBy(const float &yaw, const float &pitch)");

	this->yaw += yaw;
	this->pitch -= pitch;
	this->SetDirty(true);
}

// Update camera
void Camera::UpdateCamera()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void UpdateCamera()");

	// Update front vector
	glm::vec3 angles = glm::vec3(0);
	angles.x = glm::cos(glm::radians(this->pitch)) * glm::cos(glm::radians(this->yaw));
	angles.y = glm::sin(glm::radians(this->pitch));
	angles.z = glm::cos(glm::radians(this->pitch)) * glm::sin(glm::radians(this->yaw));
	this->front = glm::normalize(angles);

	// Update other vectors
	this->right = glm::normalize(glm::cross(this->front, this->up));
	this->top = glm::normalize(glm::cross(this->right, this->front));

	// Update matrices and frustum
	this->view = glm::lookAt(this->position, this->position + this->front, this->top);
	this->projection = this->CreateProjection();
	this->SetDirty(false);
	this->UpdateFrustum();
}

// Update frustum
void Camera::UpdateFrustum()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void UpdateFrustum()");

	// Set frustum planes based on projection view matrix
	glm::mat4 pv = this->GetProjectionView();
	this->frustum[(int)Camera::Frustum::LEFT] = glm::vec4(pv[0][3] + pv[0][0], pv[1][3] + pv[1][0], pv[2][3] + pv[2][0], pv[3][3] + pv[3][0]);
	this->frustum[(int)Camera::Frustum::RIGHT] = glm::vec4(pv[0][3] - pv[0][0], pv[1][3] - pv[1][0], pv[2][3] - pv[2][0], pv[3][3] - pv[3][0]);
	this->frustum[(int)Camera::Frustum::TOP] = glm::vec4(pv[0][3] - pv[0][1], pv[1][3] - pv[1][1], pv[2][3] - pv[2][1], pv[3][3] - pv[3][1]);
	this->frustum[(int)Camera::Frustum::BOTTOM] = glm::vec4(pv[0][3] + pv[0][1], pv[1][3] + pv[1][1], pv[2][3] + pv[2][1], pv[3][3] + pv[3][1]);
	this->frustum[(int)Camera::Frustum::NEAR] = glm::vec4(pv[0][3] + pv[0][2], pv[1][3] + pv[1][2], pv[2][3] + pv[2][2], pv[3][3] + pv[3][2]);
	this->frustum[(int)Camera::Frustum::FAR] = glm::vec4(pv[0][3] - pv[0][2], pv[1][3] - pv[1][2], pv[2][3] - pv[2][2], pv[3][3] - pv[3][2]);

	// Normalize frustum planes
	for (int i = 0; i < 6; ++i)
	{
		this->frustum[i] /= glm::length(glm::vec3(this->frustum[i]));
	}
}

// Set field of view
void Camera::SetFOV(const float &value)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void SetFOV(const float &value)");

	this->fov = value;
	this->UpdateCamera();
}

// Set near
void Camera::SetNear(const float &value)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void SetNear(const float &value)");

	this->near = value;
	this->UpdateCamera();
}

// Set far
void Camera::SetFar(const float &value)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void SetFar(const float &value)");

	this->far = value;
	this->UpdateCamera();
}

// Set camera dirty
void Camera::SetDirty(const bool &value)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "void SetDirty(const bool &value)");

	this->isDirty = value;
}

// Check point in frustum
bool Camera::IsPointInFrustum(const glm::vec3 &point)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "bool IsPointInFrustum(const glm::vec3 &point)");

	// Update camera if dirty
	if (this->isDirty)
	{
		this->UpdateCamera();
	}

	// Check each frustum plane
	for (int i = 0; i < 6; ++i)
	{
		if (glm::dot(glm::vec3(this->frustum[i]), point) + this->frustum[i].w < 0.0f)
		{
			return false;
		}
	}
	return true;
}

// Check bounding box in frustum
bool Camera::IsAABBInFrustum(const AABB &aabb)
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "bool IsAABBInFrustum(const AABB &aabb)");

	// Update camera if dirty
	if (this->isDirty)
	{
		this->UpdateCamera();
	}

	// Check each frustum plane
	for (int i = 0; i < 6; ++i)
	{
		// Check each bounding box vertex
		for (int j = 0; j < 8; ++j)
		{
			if (glm::dot(glm::vec3(this->frustum[i]), aabb.GetVertex(j)) + this->frustum[i].w >= 0.0f)
			{
				return false;
			}
		}
	}
	return true;
}

// Get position
glm::vec3 Camera::GetPosition() const
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::vec3 GetPosition() const");

	return this->position;
}

// Get front vector
glm::vec3 Camera::GetFront()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::vec3 GetFront()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->front;
}

// Get right vector
glm::vec3 Camera::GetRight()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::vec3 GetRight()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->right;
}

// Get top vector
glm::vec3 Camera::GetTop()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::vec3 GetTop()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->top;
}

// Get near
float Camera::GetNear() const
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "float GetNear() const");

	return this->near;
}

// Get far
float Camera::GetFar() const
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "float GetFar() const");

	return this->far;
}

// Get view matrix
glm::mat4 Camera::GetView()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::mat4 GetView()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->view;
}

// Get projection matrix
glm::mat4 Camera::GetProjection()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::mat4 GetProjection()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->projection;
}

// Get projection and view product matrix
glm::mat4 Camera::GetProjectionView()
{
	Logger::LogTrace(ModuleData::Name::CAMERA, "glm::mat4 GetProjectionView()");

	if (this->isDirty)
	{
		this->UpdateCamera();
	}
	return this->projection * this->view;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
