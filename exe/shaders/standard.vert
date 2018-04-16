#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(std140, binding = 1) buffer MatrixBuffer
{
  mat4 mvp;
  mat4 modelView;
  mat4 normal;
};
out vec3 out_normal;
out vec4 eye;
void main()
{
  out_normal = mat3(normal) * in_normal;
  eye = -(modelView * vec4(in_position, 1));
  gl_Position = mvp * vec4(in_position, 1);
}
