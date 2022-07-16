////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

layout (location = 0) in vec3 vPosition;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 fTexCoord;
out vec3 fPosition;

void main()
{
  gl_Position = uProjection * uView * vec4(vPosition, 1.0);
  fTexCoord = vec3(vPosition.x, vPosition.y, vPosition.z * -1);
  fPosition = vPosition;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
