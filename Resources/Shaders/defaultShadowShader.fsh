#version 120

precision lowp float;

varying vec2 UV;
varying vec4 ShadowCoord;

uniform sampler2D myTextureSampler;
uniform sampler2DShadow shadowMap;
varying vec3 vertexPosition_worldspace;

#define ITERATIONS 3

vec2 poissonDisk[16] = vec2[]( 
   vec2(-0.94201624, -0.39906216), 
   vec2(0.94558609, -0.76890725), 
   vec2(-0.094184101, -0.92938870), 
   vec2(0.34495938, 0.29387760), 
   vec2(-0.91588581, 0.45771432), 
   vec2(-0.81544232, -0.87912464), 
   vec2(-0.38277543, 0.27676845), 
   vec2(0.97484398, 0.75648379), 
   vec2(0.44323325, -0.97511554), 
   vec2(0.53742981, -0.47373420), 
   vec2(-0.26496911, -0.41893023), 
   vec2(0.79197514, 0.19090188), 
   vec2(-0.24188840, 0.99706507), 
   vec2(-0.81409955, 0.91437590), 
   vec2(0.19984126, 0.78641367), 
   vec2(0.14383161, -0.14100790) 
);

/*vec2 getPoison(float i) {
	
	int index = int(mod(i, 16));
	float size = 1250.f;
	
	if (index == 0) return vec2( -0.94201624, -0.39906216 ) / size;
	else if (index == 1) return vec2( 0.14383161, -0.14100790 ) / size;
	else if (index == 2) return vec2( 0.94558609, -0.76890725 ) / size;
	else if (index == 3) return vec2( -0.094184101, -0.92938870 ) / size;
	else if (index == 4) return vec2( 0.34495938, 0.29387760 ) / size;
	else if (index == 5) return vec2( -0.91588581, 0.45771432 ) / size;
	else if (index == 6) return vec2( -0.81544232, -0.87912464 ) / size;
	else if (index == 7) return vec2( -0.38277543, 0.27676845 ) / size;
	else if (index == 8) return vec2( 0.97484398, 0.75648379 ) / size;
	else if (index == 9) return vec2( 0.44323325, -0.97511554 ) / size;
	else if (index == 10) return vec2( 0.53742981, -0.47373420 ) / size;
	else if (index == 11) return vec2( -0.26496911, -0.41893023 ) / size;
	else if (index == 12) return vec2( 0.79197514, 0.19090188 ) / size;
	else if (index == 13) return vec2( -0.24188840, 0.99706507 ) / size;
	else if (index == 14) return vec2( -0.81409955, 0.91437590 ) / size;
	else if (index == 15) return vec2( 0.19984126, 0.78641367 ) / size;
	else return vec2( 0.14383161, -0.14100790 ) / size;

}*/

void main() {

	float visibility = 1.0;
	for (int i = 0; i < ITERATIONS; i++){
		visibility -= 0.4 / ITERATIONS * (1.0 - shadow2D(shadowMap, vec3(ShadowCoord.xy + poissonDisk[i] / 1250.f, (ShadowCoord.z - 0.001) / ShadowCoord.w)).r);
	}

	gl_FragColor = vec4(visibility * texture2D(myTextureSampler, UV).rgb, 1.f);

}