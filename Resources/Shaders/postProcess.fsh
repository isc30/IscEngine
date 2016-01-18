#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
	vec2 UV_post = UV;
	UV_post.x += sin(UV_post.y * 2 * 3.14159 + time) / 100;
	gl_FragColor = texture2D( renderedTexture, UV_post ) ;
}