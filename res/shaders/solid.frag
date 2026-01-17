////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

in vec2 fTexCoord;
in vec3 fNormal;
in float fAmbient;
in vec2 fLight;

uniform float uTime;
uniform sampler2D uFragTexture;
uniform sampler2D uBloomTexture;

layout (location = 0) out vec4 rFragColor;
layout (location = 1) out vec4 rBloomColor;

const float light[4] = float[](1.0, 0.8, 0.6, 0.3);
const float timeSpeed = 0.03;

float GetFaceLight(vec3 normal)
{
	if (normal.x != 0.0)
	{
		return 0.8;
	}
	if (normal.y > 0.0)
	{
		return 1.0;
	}
	if (normal.y < 0.0)
	{
		return 0.4;
	}
	if (normal.z != 0.0)
	{
		return 0.6;
	}
}

void main()
{
	vec4 sample = texture(uFragTexture, fTexCoord);
	if (sample.a < 0.5)
	{
		discard;
	}

	float ambient = clamp((fAmbient + 1.0) / 4.0, 0.5, 1.0);
	float light = clamp(fLight.x / 15.0, 0.0, 1.0);
	float sun = clamp((fLight.y / 15.0) * ((sin(uTime * timeSpeed) + 1) / 2.0), 0.2, 1.0);
	vec3 color = (sample.rgb * GetFaceLight(fNormal) * ambient) * max(light, sun);

	rFragColor = vec4(color, sample.a);
	rBloomColor = texture(uBloomTexture, fTexCoord);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
