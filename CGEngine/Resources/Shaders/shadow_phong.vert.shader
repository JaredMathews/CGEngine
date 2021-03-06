#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;
uniform mat4 mxMLP;

out vec4 outFragmentPosition;
out vec3 outFragmentNormal;
out vec2 outFragmentTexCoord;
out vec4 shadowCoordFragment;

void main()
{
	outFragmentPosition = (mxModelView)* vec4(vertexPosition, 1.0);
	outFragmentNormal = mxNormal * vertexNormal;
	outFragmentTexCoord = vertexUV;
	shadowCoordFragment = mxMLP * vec4(vertexPosition, 1.0);
	gl_Position = mxMVP * vec4(vertexPosition, 1.0);
}