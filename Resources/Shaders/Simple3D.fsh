#version 120

precision lowp float;

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

uniform int lightCount;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

struct LightSource {

	vec3 position_worldspace;
	vec3 color;
	float power;

};

uniform LightSource lights[2];

vec3 applyLight(LightSource light, vec3 surfaceColor, vec3 normal, vec3 surfacePosition, vec3 surfaceToCamera) {

	vec3 surfaceToLight = normalize(light.position_worldspace - surfacePosition);
	float distanceToLight = length(light.position_worldspace - surfacePosition);
	float attenuation = 1.0 / (0.5f + 1.f / (light.power * 10) * pow(distanceToLight, 2));

	float diffuseCoefficient = max(0.f, dot(normal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.color;

	float specularCoefficient = 0.f;
	if (diffuseCoefficient > 0.f)
		specularCoefficient = pow(max(0.f, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), 75.f); // 80 = materialShininess
	vec3 specular = specularCoefficient * light.color * vec3(0.3f, 0.3f, 0.3f); // * materialSpecularColor

	return attenuation * (diffuse + specular);
	
}

void main(){
	
	vec3 finalColor = vec3(0, 0, 0);
	for (int i = 0; i < lightCount; i++) {
		finalColor += applyLight(lights[i], texture2D(myTextureSampler, UV).rgb, normalize(Normal_worldspace), Position_worldspace, normalize(cameraPosition_worldspace - Position_worldspace));
	}

	vec3 ambient = vec3(0.2f, 0.2f, 0.2f) * texture2D(myTextureSampler, UV).rgb;
	gl_FragColor.rgb = ambient + finalColor;
	gl_FragColor.a = 1.f;

	/* GAMMA CORRECTION
	vec3 gamma = vec3(1 / 2.2f);
    gl_FragColor.rgb = pow(gl_FragColor.rgb, gamma);*/

}