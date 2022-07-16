////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Skybox.h"

// Constructor
Skybox::Skybox(const char* path)
{
  // Setup vertices and attributes
  std::vector<float> vertices = std::vector<float>({
    // Front
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

    // Right
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,

    // Back
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		// Left
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		// Top
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,

		 // Bottom
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
	});
  std::vector<int> attributes = std::vector<int>({ 3 });

  // Setup texture and object
  this->texture = new Cubemap(path);
  this->cube = new Object(glm::vec3(0), vertices, attributes);
  this->cube->SetShader(ShaderManager::SetShader("skybox"));
  this->GetShader()->SetInt("uCubemap", 0);
}

// Destructor
Skybox::~Skybox()
{
  delete this->texture;
  delete this->cube;
}

// Render skybox
void Skybox::Render(Camera& camera)
{
  // Setup shader and texture
  this->texture->Bind(0);
  this->GetShader()->SetMatrix4("uProjection", camera.GetProjection());
  this->GetShader()->SetMatrix4("uView", glm::mat4(glm::mat3(camera.GetView())));

  // Render
  glDepthMask(GL_FALSE);
  this->cube->Render();
  glDepthMask(GL_TRUE);
}

// Get shader
Shader* Skybox::GetShader()
{
  return this->cube->GetShader();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
