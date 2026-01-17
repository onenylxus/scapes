////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "Mesh.h"

// Get mesh data for skybox
Mesh::Data Mesh::Skybox()
{
	Logger::LogTrace(ModuleData::Name::MESH, "Mesh::Data Skybox()");

	Mesh::Data data;
	data.vertices = Mesh::LoadVertexDataFromFile("res/meshes/skybox_vertex_data.txt", 3);
	data.attr = Mesh::AttributeData({3});
	data.indices = Mesh::IndexData();
	return data;
}

// Get mesh data for cube
Mesh::Data Mesh::Cube()
{
	Logger::LogTrace(ModuleData::Name::MESH, "Mesh::Data Cube()");

	Mesh::Data data;
	data.vertices = Mesh::LoadVertexDataFromFile("res/meshes/cube_vertex_data.txt", 8);
	data.attr = Mesh::AttributeData({3, 3, 2});
	data.indices = Mesh::IndexData();
	return data;
}

// Get mesh data for quad
Mesh::Data Mesh::Quad()
{
	Logger::LogTrace(ModuleData::Name::MESH, "Mesh::Data Quad()");

	Mesh::Data data;
	data.vertices = Mesh::LoadVertexDataFromFile("res/meshes/quad_vertex_data.txt", 8);
	data.attr = Mesh::AttributeData({3, 3, 2});
	data.indices = Mesh::IndexData();
	return data;
}

// Load vertex data from file
Mesh::VertexData Mesh::LoadVertexDataFromFile(const char *path, const int attrSize)
{
	Logger::LogTrace(ModuleData::Name::MESH, "Mesh::VertexData LoadVertexDataFromFile(const char *path, const int attrSize)");

	std::vector<float> vertexData;
	FILE *file = fopen(path, "r");
	if (file == nullptr)
	{
		Logger::LogError(ModuleData::Name::MESH, "Failed to open vertex data file: %s", path);
		return vertexData;
	}

	float value;
	while (fscanf(file, "%f,", &value) == 1)
	{
		vertexData.push_back(value);
	}
	fclose(file);

	if (vertexData.empty())
	{
		Logger::LogError(ModuleData::Name::MESH, "Vertex data file is empty: %s", path);
		return vertexData;
	}
	if (vertexData.size() % attrSize != 0)
	{
		Logger::LogError(ModuleData::Name::MESH, "Vertex data file is malformed: %s", path);
		return vertexData;
	}
	Logger::LogInfo(ModuleData::Name::MESH, "Loaded vertex data from file: %s", path);
	return vertexData;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
