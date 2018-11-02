#version 430 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture10;

in vec2 out_uv;

void main()
{
    float distance = texture2D(texture10, out_uv).a;
    float alpha = smoothstep(0.5 - 0.2, 0.5 + 0.2, distance);
    out_color = vec4(vec3(1, 1, 1) * alpha, alpha);
}