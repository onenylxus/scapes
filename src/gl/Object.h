////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../gl/Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"

class Object
{
public:
	struct Data
	{
		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ebo = 0;
		int size;
	};

public:
	Object(const glm::vec3 &position, const std::vector<float> &data, const std::vector<int> &attr, const std::vector<unsigned int> &indices = std::vector<unsigned int>());
	Object(const glm::vec3 &position, const Mesh::Data &data);
	virtual ~Object();

private:
	Object::Data data;
	Transform *transform;
	Shader *shader;

public:
	void BindVAO() const;
	void BindVBO() const;
	void Render(Camera &camera);
	void Render();

public:
	void SetShader(Shader *shader);

public:
	Shader *GetShader() const;
	glm::vec3 GetPosition();
	Transform *GetTransform();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
