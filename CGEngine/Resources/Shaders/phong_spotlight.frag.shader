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
	vec3 direction;
	float exponent;
	float cutoff;
};

uniform Light lights[5];

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

void phong(int lightIndex, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	vec3 directionToLight = normalize(vec3(lights[lightIndex].position) - position);
	vec3 spotDirection = normalize(lights[lightIndex].direction);
	float angle = acos(dot(-directionToLight, spotDirection));

	float diffuseIntensity = max(dot(directionToLight, outFragmentNormal), 0.0);

	//vec3 ambient = material.ambient * light.ambient;

	if (angle < lights[lightIndex].cutoff)
	{
		float spotFactor = pow(dot(-directionToLight, spotDirection), lights[lightIndex].exponent);
		diffuse = vec3(lights[lightIndex].diffuse * material.diffuse * diffuseIntensity) * spotFactor;

		if (diffuseIntensity > 0.0)
		{
			vec3 positionToView = normalize(-outFragmentPosition.xyz);
			vec3 reflectLightVector = reflect(-directionToLight, outFragmentNormal);
			float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
			specularIntensity = pow(specularIntensity, material.shininess);

			specular = vec3(lights[lightIndex].specular * material.specular * specularIntensity) * spotFactor;
		}
	}
	else
	{
		//ambientDiffuse = ambient;
		specular = vec3(0.0f, 0.0f, 0.0f);
	}

}

void main()
{
	//vec3 ambientDiffuse;
	//vec3 specular;
	//phong(vec3(outFragmentPosition), outFragmentNormal, ambientDiffuse, specular);

	//outFragmentColor = vec4(ambientDiffuse + specular, 1.0);

	vec3 color = material.ambient;
	for (int i = 0; i < 5; i++)
	{
		vec3 diffuse;
		vec3 specular;
		phong(i, vec3(outFragmentPosition), outFragmentNormal, diffuse, specular);
		color += (diffuse + specular);
	}

	outFragmentColor = vec4(color, 1.0);
}
