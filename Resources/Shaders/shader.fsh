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
	vec3 MaterialSpecularColor = vec3(0.1, 0.1, 0.1);

	LightResult results[2];
	vec3 finalColor = vec3(0.f, 0.f, 0.f);

	for (int i = 0; i < 2; i++) {
		
		vec3 lightPosition_cameraspace = (V * M * vec4(lights[i].position_worldspace, 1)).xyz;
		float distance = length(lights[i].position_worldspace - Position_worldspace);
		vec3 n = normalize(Normal_cameraspace);
		vec3 l = normalize(lightPosition_cameraspace + EyeDirection_cameraspace);
		float cosTheta = clamp(dot(n, l), 0, 1);

		vec3 E = normalize(EyeDirection_cameraspace);
		vec3 R = reflect(-l, n);
		float cosAlpha = clamp(dot(E, R), 0, 1);

		results[i].diffuse = vec3(lights[i].color * lights[i].power * cosTheta / (distance * distance));
		results[i].specular = vec3(lights[i].color * lights[i].power * pow(cosAlpha, 5) / (distance * distance));

		finalColor += 
			MaterialAmbientColor +
			MaterialDiffuseColor * results[i].diffuse +
			MaterialSpecularColor * results[i].specular;
		
	}

	gl_FragColor.rgb = finalColor;
	gl_FragColor.a = 1.0;

}