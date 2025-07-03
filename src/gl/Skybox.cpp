////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#include "Skybox.h"

// Constructor
Skybox::Skybox(const char *path)
{
	Logger::LogTrace(ModuleData::Name::SKYBOX, "Skybox(const char *path)");

	// Setup texture and object
	this->texture = new Cubemap(path);
	this->cube = new Object(glm::vec3(0), Mesh::Skybox());
	this->cube->SetShader(ShaderManager::SetShader("skybox"));
}

// Destructor
Skybox::~Skybox()
{
	Logger::LogTrace(ModuleData::Name::SKYBOX, "~Skybox()");

	delete this->texture;
	delete this->cube;
}

// Render skybox
void Skybox::Render(Camera &camera)
{
	Logger::LogTrace(ModuleData::Name::SKYBOX, "void Render(Camera &camera)");

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
Shader *Skybox::GetShader()
{
	Logger::LogTrace(ModuleData::Name::SKYBOX, "Shader *GetShader()");

	return this->cube->GetShader();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
