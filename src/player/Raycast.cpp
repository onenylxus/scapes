////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
#include "Raycast.h"

// Cast ray from camera
Raycast::Ray Raycast::CastFromCamera(const float &distance, Camera &camera)
{
	Logger::LogTrace(ModuleData::Name::RAYCAST, "Raycast::Ray Raycast::CastFromCamera(const float &distance, Camera &camera)");

	// Adjust values from screen size
	glm::vec2 screenSize = Engine::GetWindowSize();
	glm::vec2 mousePosition = screenSize / 2.0f;
	if (screenSize.x == 0 || screenSize.y == 0)
	{
		return Raycast::Ray(BlockManager::Value::AIR, glm::vec3(0), BlockManager::Value::AIR, glm::vec3(0), false);
	}

	// Calculate space values
	glm::vec2 mouseNDS = glm::vec2(2.0f * mousePosition.x / screenSize.x - 1.0f, 1.0f - 2.0f * mousePosition.y / screenSize.y);
	glm::vec4 mouseEye = glm::inverse(camera.GetProjection()) * glm::vec4(mouseNDS, -1.0f, 1.0f);
	mouseEye.z = -1.0f;
	mouseEye.w = 0.0f;
	glm::vec3 direction = glm::normalize(glm::inverse(camera.GetView()) * mouseEye);

	// Process cell posiitons
	std::vector<glm::vec3> positions = std::vector<glm::vec3>();
	glm::vec3 pointStart = camera.GetPosition();
	glm::vec3 pointEnd = camera.GetPosition() + direction * distance;
	glm::vec3 cellStart = glm::floor(pointStart);
	glm::vec3 cellEnd = glm::floor(pointEnd);

	// Process direction
	int stepX = direction.x * distance >= 0 ? 1 : -1;
	int stepY = direction.y * distance >= 0 ? 1 : -1;
	int stepZ = direction.z * distance >= 0 ? 1 : -1;

	// Distance to nearest block side
	double nearX = (stepX > 0) ? cellStart.x + 1 - pointStart.x : pointStart.x - cellStart.x;
	double nearY = (stepY > 0) ? cellStart.y + 1 - pointStart.y : pointStart.y - cellStart.y;
	double nearZ = (stepZ > 0) ? cellStart.z + 1 - pointStart.z : pointStart.z - cellStart.z;
	double maxX = direction.x != 0 ? nearX / direction.x : DBL_MAX;
	double maxY = direction.y != 0 ? nearY / direction.y : DBL_MAX;
	double maxZ = direction.z != 0 ? nearZ / direction.z : DBL_MAX;
	double dx = direction.x != 0 ? 1 / direction.x : DBL_MAX;
	double dy = direction.y != 0 ? 1 / direction.y : DBL_MAX;
	double dz = direction.z != 0 ? 1 / direction.z : DBL_MAX;

	// Cast ray and count
	glm::vec3 current = pointStart;
	int gridX = std::abs(cellEnd.x - cellStart.x);
	int gridY = std::abs(cellEnd.y - cellStart.y);
	int gridZ = std::abs(cellEnd.z - cellStart.z);
	int counter = 0;

	positions.push_back(current);
	while (counter != gridX + gridY + gridZ)
	{
		if (std::abs(maxX) < std::abs(maxY))
		{
			if (std::abs(maxX) < std::abs(maxZ))
			{
				maxX += dx;
				current.x += stepX;
			}
			else
			{
				maxZ += dz;
				current.z += stepZ;
			}
		}
		else
		{
			if (std::abs(maxY) < std::abs(maxZ))
			{
				maxY += dy;
				current.y += stepY;
			}
			else
			{
				maxZ += dz;
				current.z += stepZ;
			}
		}

		BlockManager::Value value = BlockManager::Value::AIR;
		if (current.y < 0)
		{
			break;
		}
		if (value == BlockManager::Value::AIR)
		{
			++counter;
			positions.push_back(glm::floor(current));
			continue;
		}
		return Raycast::Ray(value, glm::floor(current), BlockManager::Value::AIR, positions.size() != 0 ? positions[positions.size() - 1] : current, true);
	}

	return Raycast::Ray(BlockManager::Value::AIR, glm::vec3(0), BlockManager::Value::AIR, glm::vec3(0), false);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
