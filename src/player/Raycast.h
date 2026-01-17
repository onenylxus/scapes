////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#pragma once

#include <cfloat>
#include <glm/glm.hpp>
#include "../core/Input.h"
#include "../gl/Camera.h"
#include "../manager/BlockManager.h"
#include "../view/Renderer.h"
#include "../world/World.h"

class Raycast
{
public:
	struct Ray
	{
		BlockID hitValue;
		BlockID neighborValue;
		glm::vec3 hitPosition;
		glm::vec3 neighborPosition;
		bool isHit;

		Ray(BlockID hitValue, const glm::vec3 &hitPosition, BlockID neighborValue, const glm::vec3 &neighborPosition, bool isHit)
		{
			this->hitValue = hitValue;
			this->neighborValue = neighborValue;
			this->hitPosition = hitPosition;
			this->neighborPosition = neighborPosition;
			this->isHit = isHit;
		}
	};

public:
	static Raycast::Ray CastFromCamera(const float &distance, Camera &camera);
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
