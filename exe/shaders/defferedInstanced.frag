#version 430 core
layout (location = 0) out vec4 rPosition;
layout (location = 1) out vec3 rNormal;
layout (location = 2) out vec4 rColor;

in vec4 out_position;
in vec3 out_normal;
in vec2 out_uv;

void main(void)
{
  rPosition = out_position;
  rNormal = abs(out_normal);
  rColor = vec4(out_normal, 1);
}
