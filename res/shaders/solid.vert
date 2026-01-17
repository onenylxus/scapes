////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in float vAmbient;
layout (location = 4) in vec2 vLight;

uniform vec3 uPosition;
uniform mat4 uProjectionView;

out vec2 fTexCoord;
out vec3 fNormal;
out float fAmbient;
out vec2 fLight;

void main()
{
	mat4 model = mat4(1);
	model[3] = vec4(uPosition, 1);
	glPosition = uProjectionView * model * vec4(vPosition, 1);

	fTexCoord = vTexCoord;
	fNormal = vNormal;
	fAmbient = vAmbient;
	fLight = vLight;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
