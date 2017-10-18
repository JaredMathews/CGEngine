#include "stdafx.h"
#include "scene02.h"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "input.h"

Scene02::~Scene02()
{
}

float positionData1[] =
{
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f,  0.8f, 0.0f
};

float colorData1[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

glm::vec3 vPositionData1[] =
{
	glm::vec3(-0.8f, -0.8f, 0.0f),
	glm::vec3(0.8f, -0.8f, 0.0f),
	glm::vec3(0.0f,  0.8f, 0.0f),
};

glm::vec3 vColorData1[] =
{
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
};

glm::vec3 vertexData1[] =
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

bool Scene02::Initialize()
{
	m_shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\transform.vert", "..\\Resources\\Shaders\\basic.frag");

	glGenBuffers(3, m_vboHandles);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData1), positionData1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData1), colorData1, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexBuffer(0, m_vboHandles[POSITION], 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glBindVertexBuffer(1, m_vboHandles[COLOR], 0, sizeof(glm::vec3));

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	m_engine->Get<Input>()->AddButton("click", Input::eButtonType::MOUSE, 0);
	m_engine->Get<Input>()->AddAnalog("x-axis", Input::eAnalogType::MOUSE_X, 0);
	m_engine->Get<Input>()->AddAnalog("y-axis", Input::eAnalogType::MOUSE_Y, 0);

	return true;
}

void Scene02::Render()
{
	m_engine->Update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render code
	glBindVertexArray(m_vaoHandle);

	glm::mat4 mxTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(m_x, m_y, 0.0f));
	glm::mat4 mxScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_cursorSize));

	mxTranslate = mxTranslate * mxScale;

	GLuint matrixUniform = glGetUniformLocation(m_shaderProgram, "modelMatrix");
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &mxTranslate[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene02::Update()
{
	Input::eButtonState state = m_engine->Get<Input>()->GetButton("click");
	float x = m_engine->Get<Input>()->GetAnalogAbsolute("x-axis");
	float y = m_engine->Get<Input>()->GetAnalogAbsolute("y-axis");
	m_x = (2 * (x / m_engine->Get<Renderer>()->m_width)) - 1;
	m_y = (2 * (-y / m_engine->Get<Renderer>()->m_height)) +1;

	glfwSetInputMode(m_engine->Get<Renderer>()->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Scene02::Shutdown()
{
}
