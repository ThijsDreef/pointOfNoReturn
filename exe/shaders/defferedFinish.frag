#version 430 core
layout (location = 0) out vec4 out_color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform vec3 directionalLight;

in vec2 out_uv;

float getShadow(vec4 fragPosLight) {
  // perform perspective divide
  vec3 projCoords = ((fragPosLight.xyz - 0.5) * 2.) / fragPosLight.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(texture3, projCoords.xy).r;

  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  return currentDepth > closestDepth ? 1.0 : 0.0;
}

vec4 getExposure(vec3 eye, vec3 normal, vec3 ldir, vec4 color)
{
  vec4 spec = vec4(0);
  vec3 e = vec3(normalize(eye));
  vec3 n = normalize(normal);
  ldir = normalize(ldir);
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
  vec4 diffuse = texture(texture2, out_uv);
  vec4 pos = texture(texture0, out_uv);
  out_color = getExposure(pos.xyz, texture(texture1, out_uv).xyz, directionalLight, diffuse);
  out_color += diffuse * 0.25;
}
