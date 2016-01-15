#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;
attribute vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;
varying vec4 ShadowCoord;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 DepthBiasVP;

void main(){
	
	mat4 MVP = P * V * M;

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	
	ShadowCoord = DepthBiasVP * M * vec4(vertexPosition_modelspace, 1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;

}