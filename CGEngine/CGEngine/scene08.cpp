#include "stdafx.h"
#include "scene08.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "model.h"
#include "timer.h"
#include "input.h"

#define SPOTLIGHT
#define NUM_LIGHTS 5

Scene08::~Scene08()
{
}

bool Scene08::Initialize()
{
	m_engine->Get<Input>()->AddButton("mode", Input::eButtonType::KEYBOARD, GLFW_KEY_SPACE);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	// light
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		Light* light = new Light("light", this);
		light->ambient = glm::vec3(0.2f);
		light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 position = glm::sphericalRand(4.0f);
		light->m_transform.m_position = position;
		glm::vec3 color = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 1.0f));
		light->diffuse = color;
		AddObject(light);
	}

	auto lights = GetObjects<Light>();

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texture_phong.vert.shader", GL_VERTEX_SHADER);
#ifdef SPOTLIGHT
	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong_spotlight.frag.shader", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong_directional.frag.shader", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.8f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.4f, 0.85f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	for (size_t i = 0; i < lights.size(); i++)
	{
		char uniformName[32];

		sprintf_s(uniformName, "lights[%d].diffuse", i);
		model->m_shader.SetUniform(uniformName, lights[i]->diffuse);

		sprintf_s(uniformName, "lights[%d].specular", i);
		model->m_shader.SetUniform(uniformName, lights[i]->specular);

#ifdef SPOTLIGHT
		sprintf_s(uniformName, "lights[%d].cutoff", i);
		model->m_shader.SetUniform(uniformName, glm::radians(45.0f));

		sprintf_s(uniformName, "lights[%d].exponent", i);
		model->m_shader.SetUniform(uniformName, 30.0f);
#endif
	}

	model->m_mesh.Load("..\\Resources\\ObjFiles\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	AddObject(model);

	model = new Model("plane", this);
	model->m_transform.m_scale = glm::vec3(7.0f);
	model->m_transform.m_position = glm::vec3(0.0f, -1.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texture_phong.vert.shader", GL_VERTEX_SHADER);
#ifdef SPOTLIGHT
	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong_spotlight.frag.shader", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("..\\Resources\\Shaders\\phong_directional.frag.shader", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.0f, 0.0f);
	model->m_material.m_diffuse = glm::vec3(1.0f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	for (size_t i = 0; i < lights.size(); i++)
	{
		char uniformName[32];

		sprintf_s(uniformName, "lights[%d].diffuse", i);
		model->m_shader.SetUniform(uniformName, lights[i]->diffuse);

		sprintf_s(uniformName, "lights[%d].specular", i);
		model->m_shader.SetUniform(uniformName, lights[i]->specular);

#ifdef SPOTLIGHT
		sprintf_s(uniformName, "lights[%d].cutoff", i);
		model->m_shader.SetUniform(uniformName, glm::radians(45.0f));

		sprintf_s(uniformName, "lights[%d].exponent", i);
		model->m_shader.SetUniform(uniformName, 30.0f);
#endif
	}

	model->m_mesh.Load("..\\Resources\\ObjFiles\\plane.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	AddObject(model);

	m_rotation = 0.0f;

	return true;
}

void Scene08::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene08::Update()
{
	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");

	if (m_engine->Get<Input>()->GetButton("mode") == Input::eButtonState::DOWN)
	{
		m_pointLightMode = !m_pointLightMode;
	}

	auto lights = GetObjects<Light>();
	for (size_t i = 0; i < lights.size(); i++)
	{
		// calculate light position position = view * light[i]
		float dt = m_engine->Get<Timer>()->FrameTime();

		m_rotation = m_rotation + 1.0f * dt;
		glm::quat rotation = glm::angleAxis(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		lights[i]->m_transform.m_position = rotation * glm::vec3(0.0f, 3.0f, 1.5f);
		float w = (m_pointLightMode) ? 1.0f : 0.0f;
		glm::vec4 position = camera->GetView() * glm::vec4(lights[i]->m_transform.m_position, w);

		auto models = GetObjects<Model>();
		for (auto model : models)
		{
			model->m_shader.Use();

			char uniformName[32];

			sprintf_s(uniformName, "lights[%d].position", i);
			model->m_shader.SetUniform(uniformName, position);

#ifdef SPOTLIGHT
			glm::mat3 viewDirectionMatrix = glm::mat3(camera->GetView());
			glm::vec3 direction = viewDirectionMatrix * glm::vec4(glm::vec3(0.0f, -1.0f, 0.0f), 0.0f);
			sprintf_s(uniformName, "lights[%d].direction", i);
			model->m_shader.SetUniform(uniformName, direction);
#endif
		}
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene08::Shutdown()
{
}
