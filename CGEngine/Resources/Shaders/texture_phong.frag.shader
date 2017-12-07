#version 430 core

in vec4 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentTexCoord;

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

layout(binding=0) uniform sampler2D textureSampler;
layout(binding = 1) uniform sampler2D normalMap;

layout (location=0) out vec4 outFragmentColor;

void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 specular)
{
	vec3 positionToLight = normalize(vec3(light.position) - vec3(outFragmentPosition));
	float diffuseIntensity = max(dot(positionToLight, normal), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	vec3 ambient = material.ambient;

	diffuse = diffuse * light.diffuse;
	ambient = ambient * light.ambient;

	ambientDiffuse = ambient + diffuse;

	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, normal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}
}

void main()
{
	vec3 ambientDiffuse;
	vec3 specular;

	vec3 normal = texture(normalMap, outFragmentTexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	phong(vec3(outFragmentPosition), normal, ambientDiffuse, specular);

    vec4 texColor = texture(textureSampler, outFragmentTexCoord);
	outFragmentColor = texColor * vec4(ambientDiffuse, 1.0) + vec4(specular, 1.0);
}