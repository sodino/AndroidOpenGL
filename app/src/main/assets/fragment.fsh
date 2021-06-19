#version 320 es
precision mediump float;
in vec3 tmpColor;
out vec4 fragColor;
void main() {
  fragColor = vec4(tmpColor, 1.0);
}