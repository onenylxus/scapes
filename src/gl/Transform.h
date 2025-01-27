////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../util/Logger.h"

// Transform class
class Transform
{
	// Constructor and destructor
public:
	Transform();
	virtual ~Transform();

	// Properties
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 matrix;
	bool isDirty;
	Transform *parent;

	// Methods
public:
	void Translate(const glm::vec3 &value);
	void Rotate(const glm::vec3 &value);

private:
	void Update();

	// Setters
public:
	void SetPosition(const glm::vec3 &value);
	void SetScale(const glm::vec3 &value);
	void SetRotation(const glm::vec3 &value);
	void SetDirty(const bool &value);
	void SetParent(Transform *parent);

	// Getters
public:
	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	glm::quat GetRotation() const;
	glm::mat4 GetMatrix();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
