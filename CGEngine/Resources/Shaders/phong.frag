#version 430 core

in vec4 outFragmentPosition;
in vec3 outFragmentNormal;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform vec3 lightPosition;
uniform vec3 lightColor;

layout (location=0) out vec4 outFragmentColor;

void main()
{
	vec3 positionToLight = normalize(vec3(lightPosition - vec3(outFragmentPosition)));
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), 0.0);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec3 specular = vec3(0.0);
	if (diffuseIntensity > 0.0)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz);
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
		specularIntensity = pow(specularIntensity, 1.0);
		specular = lightColor * specularMaterial * specularIntensity;
	}


	vec3 ambient = ambientMaterial;
	outFragmentColor = vec4(vec3(ambient + diffuse + specular), 1.0);
}