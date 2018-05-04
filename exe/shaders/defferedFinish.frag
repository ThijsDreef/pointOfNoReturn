#version 430 core
layout (location = 0) out vec4 out_color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 out_uv;

vec4 getExposure(vec3 eye, vec3 normal, vec3 ldir, vec4 color)
{
  vec4 spec = vec4(0);
  vec3 e = vec3(normalize(eye));
  vec3 n = normalize(normal);
  float power = max(dot(n, ldir), 0.0);
  if (power > 0.0)
  {
    vec3 h = normalize(ldir + e);
    float intSpec = max(dot(h,n), 0.0);
    spec = vec4(0.5) * pow(intSpec, 5);
  }
  return color * min(power, 1);
}

void main(void)
{
  out_color = getExposure(texture(texture0, out_uv).xyz, texture(texture1, out_uv).xyz, vec3(0, 0.5, 1.0), texture(texture2, out_uv));
}
