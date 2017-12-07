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

layout (location=0) out vec4 outFragmentColor;

void main()
{
	vec3 positionToLight = normalize(vec3(light.position) - vec3(outFragmentPosition));
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	vec4 diffuse = vec4(light.diffuse * material.diffuse * diffuseIntensity, 1.0);

	vec4 specular = vec4(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = vec4(light.specular * material.specular * specularIntensity, 1.0);
	}

    vec4 texColor = texture(textureSampler, outFragmentTexCoord);

	vec4 ambient = vec4(material.ambient, 1.0);
	outFragmentColor = (texColor * (ambient + diffuse)) + specular;
}