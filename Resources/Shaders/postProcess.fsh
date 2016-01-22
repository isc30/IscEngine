#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float time;

void main(){

	gl_FragColor = texture2D(renderedTexture, UV);

}