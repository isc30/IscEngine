#version 120

precision lowp float;

// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec3 Position_worldspace;
varying vec3 Normal_worldspace;
varying vec3 tangent_worldspace;
varying vec3 bitangent_worldspace;

varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
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

struct Material {
	
	bool hasNormalMap; sampler2D normalMap;
	bool hasDiffuseMap; sampler2D diffuseMap;
	bool hasSpecularMap; sampler2D specularMap;

	float shininess;
	vec3 specularColor;

};

uniform Material material;

uniform LightSource lights[100];

vec3 applyLight(LightSource light, vec3 diffuseMap, vec3 specularMap, vec3 surfaceNormal, vec3 surfacePosition, vec3 surfaceToCamera) {

	vec3 surfaceToLight = normalize(light.position_worldspace - surfacePosition);
	float distanceToLight = length(light.position_worldspace - surfacePosition);
	float attenuation = 1.0 / (0.5f + 1.f / (light.power * 10) * pow(distanceToLight, 2));

	float diffuseCoefficient = max(0.f, dot(surfaceNormal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * diffuseMap.rgb * light.color;

	float specularCoefficient = 0.f;
	if (diffuseCoefficient > 0.f && material.shininess > 0.f)
		specularCoefficient = pow(max(0.f, dot(surfaceToCamera, reflect(-surfaceToLight, surfaceNormal))), material.shininess);
	vec3 specular = specularCoefficient * light.color * vec3(0.3f, 0.3f, 0.3f) * material.specularColor * specularMap;

	return attenuation * (diffuse + specular);
	
}

void main(){
	
	vec3 surfaceToCamera = normalize(cameraPosition_worldspace - Position_worldspace);
	
	vec3 T = normalize(tangent_worldspace);
	vec3 B = normalize(bitangent_worldspace);
	vec3 N = normalize(Normal_worldspace);
	mat3 TBN = mat3(T, B, N);

	vec3 diffuseMap = material.hasDiffuseMap ? texture2D(material.diffuseMap, UV).rgb : vec3(0.75f, 0.75f, 0.75f);
	vec3 specularMap = material.hasSpecularMap ? texture2D(material.specularMap, UV).rgb : vec3(1, 1, 1);
	vec3 normalMap = material.hasNormalMap ? normalize(TBN * normalize(texture2D(material.normalMap, UV).rgb * 2.0 - 1.0)) : normalize(Normal_worldspace);

	vec3 finalColor = vec3(0, 0, 0);
	for (int i = 0; i < lightCount; i++) {
		finalColor += applyLight(lights[i], diffuseMap, specularMap, normalMap, Position_worldspace, surfaceToCamera);
	}
	finalColor = clamp(finalColor, 0, 0.8f);

	vec3 ambient = vec3(0.2f, 0.2f, 0.2f) * diffuseMap;
	gl_FragColor.rgb = ambient + finalColor;
	gl_FragColor.a = 1.f;

	/* GAMMA CORRECTION
	vec3 gamma = vec3(1 / 2.2f);
    gl_FragColor.rgb = pow(gl_FragColor.rgb, gamma);*/

}