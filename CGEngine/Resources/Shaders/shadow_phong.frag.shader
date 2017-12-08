#version 430 core

in vec4 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentTexCoord;
in vec4 shadowCoordFragment;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

struct Light
{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

layout(location = 0) out vec4 outFragmentColor;

layout(binding = 0) uniform sampler2D diffuseMap;
layout(binding = 1) uniform sampler2DShadow shadowMap;

float calculateShadow()
{
	float bias = 0.005;
	// shadow = 1.0 (not in shadow)
	// shadow = 0.0 (in shadow)
	float shadow = texture(shadowMap, vec3(shadowCoordFragment.xy, (shadowCoordFragment.z) / shadowCoordFragment.w) - bias);

	return shadow;
}

void phong(vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	vec3 positionToLight = normalize(vec3(light.position) - vec3(position));
	float diffuseIntensity = max(dot(positionToLight, normal), 0.0);
	diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-position.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, normal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}
}

void main()
{
	vec3 ambient = material.ambient;
	vec3 diffuse;
	vec3 specular;
	phong(vec3(outFragmentPosition), outFragmentNormal, diffuse, specular);

	vec4 textureColor = texture(diffuseMap, outFragmentTexCoord);
	float shadow = calculateShadow();
	outFragmentColor = textureColor * vec4(ambient + ((diffuse + specular) * shadow), 1.0);
}