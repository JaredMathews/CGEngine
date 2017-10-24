#version 430 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec3 outVertexColor;

void main()
{
	vec3 tNormal = mxNormal * vertexNormal;
	vec4 mvPosition = (mxModelView) * vec4(vertexPosition, 1.0);
	vec3 positionToLight = normalize(vec3(lightPosition - vec3(mvPosition)));
	float diffuseIntensity = max(dot(positionToLight, tNormal), 0.0);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec3 ambient = ambientMaterial;
	outVertexColor = ambient + diffuse;
	gl_Position = mxMVP * vec4(vertexPosition, 1.0);
}