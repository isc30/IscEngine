#version 120

varying vec2 UV;
varying vec4 ShadowCoord;

uniform sampler2D myTextureSampler;
uniform sampler2DShadow shadowMap;

void main() {
	
	// Material properties
	vec3 MaterialDiffuseColor = texture2D(myTextureSampler, UV).rgb;

	float bias = 0.0015;

	float visibility = 1.0;
	int iterations = 4;
	for (int i = 0; i < iterations; i++){
		visibility -= 0.4 / iterations * (1.0 - shadow2D(shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z - bias) / ShadowCoord.w)).r);
	}

	gl_FragColor.rgb = visibility * MaterialDiffuseColor;
	gl_FragColor.a = 1.f;

}