#version 430 core
layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 out_uv;
void main()
{
    out_uv = in_uv;
    gl_Position = vec4(vec3(in_position, 0.5), 1);
}