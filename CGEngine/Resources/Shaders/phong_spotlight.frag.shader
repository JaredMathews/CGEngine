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
	vec3 directionToLight = normalize(vec3(light.position) - position);
	vec3 spotDirection = normalize(light.direction);
	float angle = acos(dot(-directionToLight, spotDirection));

	float diffuseIntensity = max(dot(directionToLight, outFragmentNormal), 0.0);
	//vec3 diffuse = vec3(material.diffuse * diffuseIntensity);

	vec3 ambient = material.ambient * light.ambient;

	if (angle < light.cutoff)
	{
		float spotFactor = pow(dot(-directionToLight, spotDirection), light.exponent);
		vec3 diffuse = vec3(light.diffuse * material.diffuse * diffuseIntensity) * spotFactor;

		//diffuse = diffuse * light.diffuse;
		//ambient = ambient * light.ambient;

		ambientDiffuse = ambient + diffuse;

		if (diffuseIntensity > 0.0)
		{
			vec3 positionToView = normalize(-outFragmentPosition.xyz);
			vec3 reflectLightVector = reflect(-directionToLight, outFragmentNormal);
			float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
			specularIntensity = pow(specularIntensity, material.shininess);

			specular = vec3(light.specular * material.specular * specularIntensity) * spotFactor;
		}
	}
	else
	{
		ambientDiffuse = ambient;
		specular = vec3(0.0f, 0.0f, 0.0f);
	}

}

void main()
{
	vec3 ambientDiffuse;
	vec3 specular;
	phong(vec3(outFragmentPosition), outFragmentNormal, ambientDiffuse, specular);

	outFragmentColor = vec4(ambientDiffuse + specular, 1.0);
}


//void main()
//{
//	vec3 positionToLight;
//	if (light.position.w == 0)
//	{
//		positionToLight = normalize(vec3(light.position));
//	}
//	else
//	{
//		positionToLight = normalize(vec3(vec3(light.position) - vec3(outFragmentPosition)));
//	}
//
//	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
//	vec4 diffuse = vec4(material.diffuse * diffuseIntensity, 1.0);
//
//	vec4 specular = vec4(0.0);
//	if (diffuseIntensity > 0.0)
//	{
//		vec3 positionToView = normalize(-outFragmentPosition.xyz);
//		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
//		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
//		specularIntensity = pow(specularIntensity, material.shininess);
//		specular = vec4(material.specular * specularIntensity, 1.0);
//	}
//
//	vec4 texColor = texture(textureSampler, outFragmentTexCoord);
//	vec4 specularColor = texture(textureSampler2, outFragmentTexCoord);
//
//	vec4 ambient = vec4(material.ambient, 1.0);
//
//	diffuse = diffuse * vec4(light.diffuse, 1.0);
//	specular = specular * vec4(light.specular, 1.0);
//	ambient = ambient * vec4(light.ambient, 1.0);
//
//	vec4 phong = ((ambient + diffuse)/* * texColor*/) + (specular /** specularColor*/);
//
//	float distance = abs(outFragmentPosition.z);
//	float fogIntensity = clamp((distance - fog.distanceMin) / (fog.distanceMax - fog.distanceMin), 0.0, 1.0);
//
//	vec4 color = mix(phong, vec4(fog.color, 1.0), fogIntensity);
//	outFragmentColor = color;
//}