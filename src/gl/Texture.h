////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>
#include "../util/Logger.h"

class Texture
{
public:
	struct Data
	{
		int width;
		int height;
		int format;
		unsigned char *data;
	};

public:
	Texture();
	virtual ~Texture();

protected:
	GLuint texture;

public:
	virtual void Bind(const unsigned int &index = 0) const;

protected:
	Texture::Data *Load(const char *path, const bool &flip = true);
	virtual void Create(const Texture::Data &data);
	void Destroy(Texture::Data *data);

public:
	int GetTexture() const;
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
