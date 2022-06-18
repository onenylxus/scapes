////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uModel;
  
out vec2 fTexCoord;

void main() {
  gl_Position = uProjection * uView * uModel * vec4(vPosition, 1.0);
  fTexCoord = vTexCoord;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
