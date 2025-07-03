////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../gl/Camera.h"
#include "../manager/ShaderManager.h"

class Renderer
{
public:
	struct Line
	{
		glm::vec3 start;
		glm::vec3 end;
		glm::vec3 color;
		unsigned int vao = 0;
		unsigned int vbo = 0;
	};

private:
	static Shader *shader;
	static std::vector<Renderer::Line> lines;

public:
	static void AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color = glm::vec3(0.5f));
	static void AddBox(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));
	static void Render(Camera &camera);
	static void Clear();
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
