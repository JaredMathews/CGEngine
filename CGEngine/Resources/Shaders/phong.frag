#version 430 core

in vec4 outFragmentPosition;
in vec3 outFragmentNormal;

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

layout (location=0) out vec4 outFragmentColor;

void main()
{
	vec3 positionToLight = normalize(vec3(light.position) - vec3(outFragmentPosition));
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}


	vec3 ambient = material.ambient;
	outFragmentColor = vec4(vec3(ambient + diffuse + specular), 1.0);
}