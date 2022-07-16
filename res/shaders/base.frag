////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

in vec2 fTexCoord;
in vec3 fNormal;

out vec4 rColor;

void main()
{
  rColor = vec4((fNormal + 1.0) / 2, 1.0);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
