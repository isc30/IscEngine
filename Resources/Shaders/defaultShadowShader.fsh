#version 120

varying vec2 UV;
varying vec4 ShadowCoord;

uniform sampler2D myTextureSampler;
uniform sampler2DShadow shadowMap;
varying vec3 vertexPosition_worldspace;

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed, i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

vec2 getPoison(float i) {
	
	vec2 poisonValue = vec2(0.f, 0.f);
	switch (int(mod(i, 16))) {
		
		default: case 0: poisonValue = vec2( -0.94201624, -0.39906216 ); break;
		case 1: poisonValue = vec2( 0.14383161, -0.14100790 ); break;
		case 2: poisonValue = vec2( 0.94558609, -0.76890725 ); break;
		case 3: poisonValue = vec2( -0.094184101, -0.92938870 ); break;
		case 4: poisonValue = vec2( 0.34495938, 0.29387760 ); break;

		case 5: poisonValue = vec2( -0.91588581, 0.45771432 ); break;
		case 6: poisonValue = vec2( -0.81544232, -0.87912464 ); break;
		case 7: poisonValue = vec2( -0.38277543, 0.27676845 ); break;
		case 8: poisonValue = vec2( 0.97484398, 0.75648379 ); break;
		case 9: poisonValue = vec2( 0.44323325, -0.97511554 ); break;
		case 10: poisonValue = vec2( 0.53742981, -0.47373420 ); break;
		case 11: poisonValue = vec2( -0.26496911, -0.41893023 ); break;
		case 12: poisonValue = vec2( 0.79197514, 0.19090188 ); break;
		case 13: poisonValue = vec2( -0.24188840, 0.99706507 ); break;
		case 14: poisonValue = vec2( -0.81409955, 0.91437590 ); break;
		case 15: poisonValue = vec2( 0.19984126, 0.78641367 ); break;
	
	}
	
	return poisonValue / 1500.f;

}

void main() {
	
	// Material properties
	vec3 MaterialDiffuseColor = texture2D(myTextureSampler, UV).rgb;

	float bias = 0.001;

	float visibility = 1.0;
	int iterations = 4;
	for (int i = 0; i < iterations; i++){
		vec2 poison = getPoison(i);
		visibility -= 0.4 / iterations * (1.0 - shadow2D(shadowMap, vec3(ShadowCoord.xy + poison, (ShadowCoord.z - bias) / ShadowCoord.w)).r);
	}

	gl_FragColor.rgb = visibility * MaterialDiffuseColor;
	gl_FragColor.a = 1.f;

}