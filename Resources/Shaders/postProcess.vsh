#version 120

attribute vec3 vertexPosition_modelspace;

varying vec2 UV;

void main(){
	gl_Position =  vec4(vertexPosition_modelspace, 1);
	UV = (vertexPosition_modelspace.xy + vec2(1, 1)) / 2.0;
}