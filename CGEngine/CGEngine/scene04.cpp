#include "stdafx.h"
#include "scene04.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"

//#define SPECULAR

Scene04::~Scene04()
{
}

float positionData3[] =
{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float colorData3[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

glm::vec3 vPositionData3[] =
{
	glm::vec3(-0.8f, -0.8f, 0.0f),
	glm::vec3(0.8f, -0.8f, 0.0f),
	glm::vec3(0.0f,  0.8f, 0.0f),
};

glm::vec3 vColorData3[] =
{
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
};

glm::vec3 vertexData3[] =
{
	glm::vec3(-0.8f, -0.8f, 0.0f),
	glm::vec3(1.0f,  0.0f, 0.0f),
	glm::vec3(0.8f, -0.8f, 0.0f),
	glm::vec3(0.0f,  1.0f, 0.0f),
	glm::vec3(0.0f,  0.8f, 0.0f),
	glm::vec3(0.0f,  0.0f, 1.0f),
	glm::vec3(-0.8f, -0.8f, 0.0f),
	glm::vec3(1.0f,  0.0f, 0.0f),
};

enum vboID
{
	POSITION,
	COLOR,
	VERTEX
};

bool Scene04::Initialize()
{
	m_shaderProgram.CompileShader("..\\Resources\\Shaders\\texture_phong.vert.shader", GL_VERTEX_SHADER);
	#ifdef SPECULAR
	m_shaderProgram.CompileShader("..\\Resources\\Shaders\\texture_phong_specular.frag.shader", GL_FRAGMENT_SHADER);
	#else
	m_shaderProgram.CompileShader("..\\Resources\\Shaders\\multi_tex_phong.frag.shader", GL_FRAGMENT_SHADER);
	#endif

	m_shaderProgram.Link();
	m_shaderProgram.Use();

	GLint width = 0;
	GLint height = 0;
	GLint bpp = 0;
	const unsigned char* data = Image::LoadBMP("..\\Resources\\Textures\\crate.bmp", width, height, bpp);

	GLint width2 = 0;
	GLint height2 = 0;
	GLint bpp2 = 0;
	#ifdef SPECULAR
	const unsigned char* data2 = Image::LoadBMP("..\\Resources\\Textures\\crate_specular.bmp", width2, height2, bpp2);
	#else
	const unsigned char* data2 = Image::LoadBMP("..\\Resources\\Textures\\grass.bmp", width2, height2, bpp2);
	#endif

	if (data == nullptr)
		std::cout << "data is null" << std::endl;

	glGenBuffers(1, m_vboHandles);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData3), positionData3, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexBuffer(0, m_vboHandles[POSITION], 0, sizeof(glm::vec3) * 2 + sizeof(float) * 2);
	glBindVertexBuffer(1, m_vboHandles[POSITION], sizeof(glm::vec3), sizeof(glm::vec3) * 2 + sizeof(float) * 2);
	glBindVertexBuffer(2, m_vboHandles[POSITION], sizeof(glm::vec3) * 2, sizeof(glm::vec3) * 2 + sizeof(float) * 2);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(2, 2);

	glGenTextures(2, m_texture);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, m_texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (bpp == 32)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, m_texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (bpp2 == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (bpp2 == 32)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width2, height2, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	delete data;

	return true;
}

void Scene04::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render code
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene04::Update()
{
	m_rotation = m_rotation + m_engine->Get<Timer>()->FrameTime();
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mxModel = translate * rotate;

	glm::vec3 ambientMaterial = glm::vec3(0.2f, 0.2f, 0.2f);
	m_shaderProgram.SetUniform("ambientMaterial", ambientMaterial);

	glm::mat4 mxView = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mxProjection = glm::perspective(90.0f, (float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height, 0.01f, 10000.0f);

	glm::mat4 mxModelView = mxView * mxModel;
	m_shaderProgram.SetUniform("mxModelView", mxModelView);

	glm::mat4 mxMVP = mxProjection * mxView * mxModel;
	m_shaderProgram.SetUniform("mxMVP", mxMVP);

	glm::mat3 mxNormal = glm::mat3(mxModelView);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	m_shaderProgram.SetUniform("mxNormal", mxNormal);

	glm::vec3 lightPosition = mxView * glm::vec4(2.0f, 10.0f, 10.0f, 1.0f);
	m_shaderProgram.SetUniform("lightPosition", lightPosition);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shaderProgram.SetUniform("lightColor", lightColor);

	glm::vec3 diffuseMaterial = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shaderProgram.SetUniform("diffuseMaterial", diffuseMaterial);

	glm::vec3 specularMaterial = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shaderProgram.SetUniform("specularMaterial", specularMaterial);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	m_shaderProgram.SetUniform("textureSampler", m_texture[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	m_shaderProgram.SetUniform("textureSampler2", m_texture[1]);
}

void Scene04::Shutdown()
{
}
