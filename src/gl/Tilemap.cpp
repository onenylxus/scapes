////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Tilemap.h"

// Constructor
Tilemap::Tilemap(const char *path, const unsigned int &rows, const unsigned int &columns)
{
	Logger::LogTrace(ModuleData::Name::TILEMAP, "Tilemap(const char *path, const unsigned int &rows, const unsigned int &columns)");

	this->texture = new Sprite(path);
	this->rows = rows;
	this->columns = columns;
	this->tileWidth = 1.0f / columns;
	this->tileHeight = 1.0f / rows;
}

// Destructor
Tilemap::~Tilemap()
{
	Logger::LogTrace(ModuleData::Name::TILEMAP, "~Tilemap()");

	delete this->texture;
}

// Bind texture
void Tilemap::Bind(const unsigned int &index) const
{
	Logger::LogTrace(ModuleData::Name::TILEMAP, "void Bind(const unsigned int &index) const");

	this->texture->Bind(index);
}

// Get sprite coordinates
void Tilemap::GetSpriteCoordinates(const unsigned int &index, std::array<glm::vec2, 4> &coords) const
{
	Logger::LogTrace(ModuleData::Name::TILEMAP, "void GetSpriteCoordinates(const unsigned int &index, std::array<glm::vec2, 4> &coords) const");

	float x = index % columns;
	float y = index / rows;

	coords[0] = glm::vec2((x + 1) * this->tileWidth, y * this->tileHeight);
	coords[1] = glm::vec2(x * this->tileWidth, y * this->tileHeight);
	coords[2] = glm::vec2(x * this->tileWidth, (y + 1) * this->tileHeight);
	coords[3] = glm::vec2((x + 1) * this->tileWidth, (y + 1) * this->tileHeight);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
