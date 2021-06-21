#version 320 es
precision mediump float;
in vec3 tmpColor;
in vec2 tmpTexCoordinate;

out vec4 fragColor;
uniform sample2D texture1;

void main() {
  fragColor = texture(texture1, tmpTexCoordinate);
}