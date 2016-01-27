#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
	
	gl_FragColor.rgb = texture2D(myTextureSampler, UV).rgb;
	gl_FragColor.a = 1.f;

}