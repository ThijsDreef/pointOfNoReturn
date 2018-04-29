#version 430 core
layout (location = 0) out vec4 out_color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 out_uv;

void main(void)
{
  out_color = texture2D(texture0, out_uv);
}
