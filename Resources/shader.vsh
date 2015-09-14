#version 330 core

layout(location=0) in vec3 vertexPosition_modelspace;
layout(location=3) in vec3 colors;

uniform mat4 M;
uniform mat4 VP;

out vec3 fragColor;

void main() {	
	
	mat4 MVP = VP * M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	fragColor = colors;
	//gl_FrontColor = gl_Color;

}