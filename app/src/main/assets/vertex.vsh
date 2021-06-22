#version 320 es
// Shaders shall always begin with a version declaration. Otherwise it defaults `version 100`.
// When some new features are used, corresponding errors will be thrown.
// For example, `in` `out` features : 0:1: L0001: Storage qualifier not allowed in GLSL ES version 100

layout(location=0) in vec4 vPosition;
layout(location=3) in vec2 vTexCoordinate;

// Just as a value transfer, so naming it with 'tmp'
out vec2 tmpTexCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vPosition;
  tmpTexCoordinate = vec2(vTexCoordinate.x, vTexCoordinate.y);
}