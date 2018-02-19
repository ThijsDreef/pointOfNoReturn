#version 450 core
layout (location = 0) out vec4 out_color;
layout (std140,binding = 0) uniform materialBuffer
{
  vec4 color;
};
in vec3 out_normal;
in vec4 eye;
float ambient = 0.2;
void main(void)
{
  vec3 e = vec3(normalize(eye));
  vec3 n = normalize(out_normal);
  vec3 ldir = vec3(0, 0.5, 1);
  vec4 spec = vec4(0);
  float power = max(dot(n, ldir), 0.0);
  if (power > 0.0)
  {
    vec3 h = normalize(ldir + e);
    float intSpec = max(dot(h,n), 0.0);
    spec = vec4(0.5) * pow(intSpec, 5);
  }
  out_color = color * min(power + ambient, 1) + spec;
}
