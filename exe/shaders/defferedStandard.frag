#version 430 core
layout (location = 0) out vec3 rPosition;
layout (location = 1) out vec3 rNormal;
layout (location = 2) out vec4 rColor;

layout(std140, binding = 0) uniform materialBuffer
{
  vec4 color;
};

float ambient = 0.2;

in vec3 out_position;
in vec4 out_eye;
in vec3 out_normal;
in vec2 out_uv;

void main(void)
{
  rPosition = out_position;
  rNormal = out_normal;
  rColor = color;
}
