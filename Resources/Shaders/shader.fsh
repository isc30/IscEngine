#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 Normal_worldspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 cameraPosition_worldspace;

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

		vec3 normal = normalize(Normal_worldspace);
		vec3 surfacePosition = Position_worldspace;
		vec3 surfaceToLight = normalize(lights[i].position_worldspace - surfacePosition);
		vec3 surfaceToCamera = normalize(cameraPosition_worldspace - surfacePosition);

		float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
		vec3 diffuse = diffuseCoefficient * lights[i].power * lights[i].color;

		float specularCoefficient = 0.0;
		if (diffuseCoefficient > 0.0) specularCoefficient = pow(max(0.0f, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), 80.f);
		vec3 specular = specularCoefficient * lights[i].power / 10 * lights[i].color;
		
		float distanceToLight = length(lights[i].position_worldspace - surfacePosition);
		float attenuation = 1.0 / (0.2f * pow(distanceToLight, 2));

		finalColor.diffuse += attenuation * diffuse;
		finalColor.specular += attenuation * specular;

	}

	gl_FragColor.rgb = MaterialAmbientColor + MaterialDiffuseColor * finalColor.diffuse + MaterialSpecularColor * finalColor.specular;
	gl_FragColor.a = 1.f;

	// GAMMA CORRECTION
	vec3 gamma = vec3(1.5f);
    gl_FragColor.rgb = pow(gl_FragColor.rgb, gamma);

}