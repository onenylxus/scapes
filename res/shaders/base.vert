////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 uProjectionView;
uniform mat4 uModel;

out vec2 fTexCoord;
out vec2 fNormal;

void main()
{
	gl_Position = uProjectionView * uModel * vec4(vPosition, 1.0);
	fTexCoord = vTexCoord;
	fNormal = vNormal;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
