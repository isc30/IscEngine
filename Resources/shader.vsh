#version 330 core

layout(location=0) in vec3 vertexPosition_modelspace;
layout(location=2) in vec2 TextureCoords;

uniform mat4 M;
uniform mat4 VP;

out vec2 UV;

void main() {	
	
	mat4 MVP = VP * M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1.0f);
	UV = TextureCoords;

}