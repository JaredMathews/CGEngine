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

bool Material::LoadTextureCube(const std::string & basename, const std::vector<std::string>& suffixes, const std::string & type, GLuint activeTexture)
{
	GLuint targets[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for (int i = 0; i < 6; i++)
	{
		int width;
		int height;
		int n;
		std::string filename = basename + suffixes[i] + "." + type;
		unsigned char* image = stbi_load(filename.c_str(), &width, &height, &n, 0);
		assert(image);

		GLenum imageFormat = (n == 4) ? GL_RGBA : GL_RGB;

		glTexImage2D(targets[i], 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		if (n == 3)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)image);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}
		else if (n == 4)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)image);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}

		TextureInfo textureInfo = { activeTexture, texture, GL_TEXTURE_CUBE_MAP };
		m_textures.push_back(textureInfo);

		delete image;
	}


	return false;
}

void Material::SetTextures()
{
	for (TextureInfo textureInfo : m_textures)
	{
		glActiveTexture(textureInfo.activeTexture);
		glBindTexture(textureInfo.type, textureInfo.texture);
	}
}

GLuint Material::CreateTexture(GLuint width, GLuint height)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

void Material::AddTexture(GLuint texture, GLuint activeTexture)
{
	TextureInfo textureInfo = { activeTexture, texture };
	m_textures.push_back(textureInfo);
}
