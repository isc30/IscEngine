#version 120

attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;
//attribute vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){

	mat4 MVP = P * V * M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	UV = vertexUV;

}