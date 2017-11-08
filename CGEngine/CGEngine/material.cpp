#include "stdafx.h"
#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Material::Material()
{
	m_ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shininess = 0.5f;
}


Material::~Material()
{
}

void Material::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shininess;
}

bool Material::LoadTexture2D(const std::string & filename, GLuint activeTexture)
{
	int width;
	int height;
	int n;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &n, 0);

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(activeTexture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (n == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (n == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	TextureInfo textureInfo = { activeTexture, texture };
	m_textures.push_back(textureInfo);

	delete data;

	return true;
}

void Material::SetTextures()
{
	for (TextureInfo textureInfo : m_textures)
	{
		glActiveTexture(textureInfo.activeTexture);
		glBindTexture(GL_TEXTURE_2D, textureInfo.texture);
	}
}
