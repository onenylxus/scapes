////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2023 MIT License
////////////////////////////////////////////////////////////////

#version 450 core

in vec2 fTexCoord;
in vec3 fNormal;
in vec2 fLight;

uniform float uTime;
uniform float uPhase;
uniform sampler2D uFragTexture;

layout (location = 0) out vec4 rFragColor;
layout (location = 1) out vec4 rBloomColor;

const float light[4] = float[](1.0, 0.8, 0.6, 0.3);
const float timeSpeed = 0.03;

void main()
{
  float offset = mod(floor(uPhase * 4), 16) / 16.0;
  vec2 texCoord = fTexCoord;
  texCoord.x += offset;
  vec4 sample = texture(uFragTexture, texCoord);

  float light = clamp(fLight.x / 15.0, 0.0, 1.0);
  float sun = clamp((fLight.y / 15.0) * ((sin(uTime * timeSpeed) + 1) / 2.0), 0.2, 1.0);
  vec3 color = sample.rgb * max(light, sun);

  rFragColor = vec4(color, 0.7);
  rBloomColor = vec4(0.0, 0.0, 0.0, 0.0);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
