#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

struct LightSource {

	vec3 position_worldspace;
	//vec3 direction_cameraspace;
	vec3 color;
	float power;

};
uniform LightSource lights[2];

struct LightResult {

	vec3 diffuse;
	vec3 specular;

};

void main(){
	
	// Material properties
	vec3 MaterialDiffuseColor = texture2D(myTextureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.4, 0.4, 0.4) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.4, 0.4, 0.4);
	
	LightResult finalColor;
	finalColor.diffuse = vec3(0,0,0);
	finalColor.specular = vec3(0,0,0);

	for (int i = 0; i < 2; i++) {

		vec3 lightPosition_cameraspace = (V * M * vec4(lights[i].position_worldspace, 1)).xyz;
		float distance = length(lights[i].position_worldspace - Position_worldspace);
		vec3 n = normalize(Normal_cameraspace);
		vec3 l = normalize(lightPosition_cameraspace + EyeDirection_cameraspace);
		float cosTheta = abs(dot(n, l));

		vec3 E = normalize(EyeDirection_cameraspace);
		vec3 R = reflect(-l, n);
		float cosAlpha = abs(dot(E, R));

		finalColor.diffuse += vec3(lights[i].color * lights[i].power * cosTheta / (distance * distance));
		finalColor.specular += vec3(lights[i].color * lights[i].power * pow(cosAlpha, 5) / (distance * distance));
		
	}

	gl_FragColor.rgb = MaterialAmbientColor + MaterialDiffuseColor * finalColor.diffuse + MaterialSpecularColor * finalColor.specular;
	gl_FragColor.a = 1.f;

	/* GAMMA CORRECTION
	vec3 gamma = vec3(1.f / 1.2f);
    gl_FragColor.rgb = pow(gl_FragColor.rgb, gamma);*/

}