#version 320 es
precision mediump float;
in vec3 tmpColor;
in vec2 tmpTexCoordinate;

out vec4 fragColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
  fragColor = mix(texture(texture0, tmpTexCoordinate), texture(texture1, tmpTexCoordinate), 0.3) * vec4(tmpColor, 1.0);
}