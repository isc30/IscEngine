#version 120

attribute vec3 vertexPosition_modelspace;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
	gl_Position = P * V * M * vec4(vertexPosition_modelspace, 1);
}