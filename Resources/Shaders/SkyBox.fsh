#version 120

// Interpolated values from the vertex shaders
varying vec3 UV;

// Values that stay constant for the whole mesh.
uniform samplerCube cubeMapSampler;

void main(){
	
	gl_FragColor.rgb = textureCube(cubeMapSampler, UV).rgb;
	gl_FragColor.a = 1.f;

}