////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "../util/Logger.h"

// Mesh class
class Mesh
{
public:
	typedef std::vector<float> VertexData;
	typedef std::vector<int> AttributeData;
	typedef std::vector<unsigned int> IndexData;
	struct Data
	{
		Mesh::VertexData vertices;
		Mesh::AttributeData attr;
		Mesh::IndexData indices;

		void operator=(const Mesh::Data &that)
		{
			this->vertices = that.vertices;
			this->attr = that.attr;
			this->indices = that.indices;
		}
	};

public:
	static Mesh::Data Skybox();
	static Mesh::Data Cube();
	static Mesh::Data Quad();

private:
	static Mesh::VertexData LoadVertexDataFromFile(const char *path, const int attrSize);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
