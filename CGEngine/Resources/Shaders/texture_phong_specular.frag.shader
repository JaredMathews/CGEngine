#version 430 core

in vec4 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentTexCoord;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform vec3 lightPosition;
uniform vec3 lightColor;
layout(binding = 0) uniform sampler2D textureSampler;
layout(binding = 1) uniform sampler2D textureSampler2;

layout(location = 0) out vec4 outFragmentColor;

void main()
{
	vec3 positionToLight = normalize(vec3(lightPosition - vec3(outFragmentPosition)));
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	vec4 diffuse = vec4(lightColor * diffuseMaterial * diffuseIntensity, 1.0);

	vec4 specular = vec4(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, 10.0);
		specular = vec4(lightColor * specularMaterial * specularIntensity, 1.0);
	}

	vec4 texColor = texture(textureSampler, outFragmentTexCoord);
	vec4 specularColor = texture(textureSampler2, outFragmentTexCoord);

	vec4 ambient = vec4(ambientMaterial, 1.0);
	outFragmentColor = ((ambient + diffuse) * texColor) + (specular * specularColor);
}