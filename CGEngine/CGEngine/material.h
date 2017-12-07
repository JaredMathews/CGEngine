#pragma once
#include "glm/gtc/matrix_transform.hpp"

 class Material
{
public:
	Material();
	~Material();

	 struct TextureInfo
	 {
		 GLuint activeTexture;
		 GLuint texture;
	 };

	 void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	 bool LoadTexture2D(const std::string& filename, GLuint activeTexture);
	 void SetTextures();
	 static GLuint CreateTexture(GLuint width, GLuint height);
	 void AddTexture(GLuint texture, GLuint activeTexture);

public:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;

	std::vector<TextureInfo> m_textures;
};

