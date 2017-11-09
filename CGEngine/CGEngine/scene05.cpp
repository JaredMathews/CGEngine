#include "stdafx.h"
#include "scene05.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"

Scene05::~Scene05()
{
}

float positionData4[] =
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

float colorData4[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

glm::vec3 vPositionData4[] =
{
	glm::vec3(-0.8f, -0.8f, 0.0f),
	glm::vec3(0.8f, -0.8f, 0.0f),
	glm::vec3(0.0f,  0.8f, 0.0f),
};

glm::vec3 vColorData4[] =
{
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
};

glm::vec3 vertexData4[] =
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

bool Scene05::Initialize()
{
	m_camera = new Camera("camera", this);
	m_camera->Initialize(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), m_camera->GetData());

	m_shaderProgram.CompileShader("..\\Resources\\Shaders\\texture_phong.vert.shader", GL_VERTEX_SHADER);
	m_shaderProgram.CompileShader("..\\Resources\\Shaders\\texture_phong_specular.frag.shader", GL_FRAGMENT_SHADER);

	m_shaderProgram.Link();
	m_shaderProgram.Use();

	glGenBuffers(1, m_vboHandles);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData4), positionData4, GL_STATIC_DRAW);

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

	m_material.SetMaterial(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 100.0f);
	m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	Light* light = new Light("light", this);

	light->ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	light->diffuse = glm::vec3(1.0f);
	light->specular = glm::vec3(1.0f);
	light->m_transform.m_position = glm::vec3(0.0f, 1.5f, 2.0f);
	AddObject(light);

	return true;
}

void Scene05::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render code
	glBindVertexArray(m_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene05::Update()
{
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}

	Light* light = GetObject<Light>("light");

	m_rotation = m_rotation + m_engine->Get<Timer>()->FrameTime();
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mxModel = translate * rotate;

	m_camera->Update();
	glm::mat4 mxView = m_camera->GetView();
	glm::mat4 mxProjection = m_camera->GetProjection();

	glm::mat4 mxModelView = mxView * mxModel;
	m_shaderProgram.SetUniform("mxModelView", mxModelView);

	glm::mat4 mxMVP = mxProjection * mxView * mxModel;
	m_shaderProgram.SetUniform("mxMVP", mxMVP);

	glm::mat3 mxNormal = glm::mat3(mxModelView);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	m_shaderProgram.SetUniform("mxNormal", mxNormal);

	//glm::vec3 lightPosition = mxView * glm::vec4(2.0f, 10.0f, 10.0f, 1.0f);
	//m_shaderProgram.SetUniform("lightPosition", lightPosition);

	glm::vec3 lightPosition = mxView * glm::vec4(light->m_transform.m_position, 1.0f);
	m_shaderProgram.SetUniform("light.position", lightPosition);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shaderProgram.SetUniform("light.color", lightColor);

	m_shaderProgram.SetUniform("light.ambient", light->ambient);
	m_shaderProgram.SetUniform("light.diffuse", light->diffuse);
	m_shaderProgram.SetUniform("light.specular", light->specular);

	m_shaderProgram.SetUniform("material.ambient", m_material.m_ambient);
	m_shaderProgram.SetUniform("material.diffuse", m_material.m_diffuse);
	m_shaderProgram.SetUniform("material.specular", m_material.m_specular);
	m_shaderProgram.SetUniform("material.shininess", m_material.m_shininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material.m_textures[0].texture);
	m_shaderProgram.SetUniform("textureSampler", m_material.m_textures[0].texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_material.m_textures[1].texture);
	m_shaderProgram.SetUniform("textureSampler2", m_material.m_textures[1].texture);
}

void Scene05::Shutdown()
{
}
