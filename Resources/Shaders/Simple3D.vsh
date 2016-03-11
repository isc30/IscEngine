#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;
attribute vec3 vertexNormal_modelspace;
attribute vec3 vertexTangent_modelspace;
attribute vec3 vertexBitangent_modelspace;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 Normal_worldspace;
varying vec3 tangent_worldspace;
varying vec3 bitangent_worldspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){

	mat4 MVP = P * V * M;

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	/*vec3 LightPosition_cameraspace = ( V * M * vec4(LightPosition_worldspace, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;*/
	
	// Normal of the the vertex, in camera space
	Normal_worldspace = (M * vec4(vertexNormal_modelspace,0.0)).xyz;
	tangent_worldspace = (M * vec4(vertexTangent_modelspace, 0.0)).xyz;
	bitangent_worldspace = (M * vec4(vertexBitangent_modelspace, 0.0)).xyz;

	// UV of the vertex. No special space for this one.
	UV = vertexUV;

}

