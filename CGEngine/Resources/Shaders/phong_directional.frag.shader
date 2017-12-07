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

struct Fog
{
	float distanceMin;
	float distanceMax;
	vec3 color;
};

uniform Fog fog;

layout(binding = 0) uniform sampler2D textureSampler;
layout(binding = 1) uniform sampler2D textureSampler2;

layout(location = 0) out vec4 outFragmentColor;

void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 specular)
{
	vec3 positionToLight;
	if (light.position.w == 0)
	{
		positionToLight = normalize(vec3(light.position));
	}
	else
	{
		positionToLight = normalize(vec3(vec3(light.position) - vec3(outFragmentPosition)));
	}

	// ambient/diffuse lighting calculations that were in main 

	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	vec3 diffuse = vec3(material.diffuse * diffuseIntensity);

	vec3 ambient = material.ambient;

	diffuse = diffuse * light.diffuse;
	ambient = ambient * light.ambient;

	ambientDiffuse = ambient + diffuse;

	// specular calculations that were in main 

	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);

		specular = light.specular * material.specular * specularIntensity;
	}

	//vec3 positionToLight;
	//if (lights[lightIndex].position.w == 0)
	//{
	//	positionToLight = normalize(vec3(lights[lightIndex].position));
	//}
	//else
	//{
	//	positionToLight = normalize(vec3(vec3(lights[lightIndex].position) - vec3(outFragmentPosition)));
	//}

	//// ambient/diffuse lighting calculations that were in main

	//float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	//diffuse = vec3(material.diffuse * diffuseIntensity);

	////vec3 ambient = material.ambient;

	//diffuse = diffuse * lights[lightIndex].diffuse;
	////ambient = ambient * light.ambient;

	////ambientDiffuse = ambient + diffuse;

	//// specular calculations that were in main

	//if (diffuseIntensity > 0.0)
	//{
	//	vec3 positionToView = normalize(-outFragmentPosition.xyz);
	//	vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
	//	float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
	//	specularIntensity = pow(specularIntensity, material.shininess);

	//	specular = lights[lightIndex].specular * material.specular * specularIntensity;
	//}
}

void main()
{
	vec3 ambientDiffuse;
	vec3 specular;
	phong(vec3(outFragmentPosition), outFragmentNormal, ambientDiffuse, specular);

	outFragmentColor = vec4(ambientDiffuse + specular, 1.0);

	/*vec3 color = material.ambient;
	for (int i = 0; i < 5; i++)
	{
		vec3 diffuse;
		vec3 specular;
		phong(i, vec3(outFragmentPosition), outFragmentNormal, diffuse, specular);
		color += (diffuse + specular);
	}

	outFragmentColor = vec4(color, 1.0);*/
}

