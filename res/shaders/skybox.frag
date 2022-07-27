////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

in vec3 fTexCoord;
in vec3 fPosition;

uniform float uTime;
// uniform samplerCube uCubemap;

layout (location = 0) out vec4 rFragColor;
layout (location = 1) out vec4 rBloomColor;

const vec3 dayTopColor = vec3(11, 90, 182) / 255;
const vec3 dayBottomColor = vec3(57, 182, 214) / 255;
const vec3 nightTopColor = vec3(19, 21, 22) / 255;
const vec3 nightBottomColor = vec3(17, 85, 155) / 255;
const float timeSpeed = 0.03;

void main()
{
  float point = (normalize(fPosition).y + 1.0) / 2;
  float daytime = (sin(uTime * timeSpeed) + 1.0) / 2;

  vec3 dayMix = mix(dayBottomColor, dayTopColor, point);
  vec3 nightMix = mix(nightBottomColor, nightTopColor, point);
  vec3 color = mix(nightMix, dayMix, daytime);

  rFragColor = vec4(color, 1.0);
  rBloomColor = vec4(0.0, 0.0, 0.0, 1.0);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
