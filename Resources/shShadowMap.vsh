#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
	mat4 MVP = P * V * M;
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}