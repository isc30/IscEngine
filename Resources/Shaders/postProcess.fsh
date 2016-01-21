#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
	gl_FragColor = texture2D( renderedTexture, UV*0.98+vec2(0.01+sin(UV.y * 2 * 3.14159 + time) / 100, 0.01) ) ;
}