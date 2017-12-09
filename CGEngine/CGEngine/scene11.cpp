#include "stdafx.h"
#include "scene11.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "model.h"
#include "timer.h"

Scene11::~Scene11()
{
}

bool Scene11::Initialize()
{
	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	// light
	Light* light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(0.0f, 1.0f, 1.0f);
	light->ambient = glm::vec3(0.2f);
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\tang_texture_phong.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\tang_texture_phong.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\brick.png", GL_TEXTURE0);
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\brick_normal.png", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.ambient", light->ambient);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\sphere.obj", true);
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);
	model->m_mesh.BindVertexAttrib(3, Mesh::eVertexType::TANGENT);

	AddObject(model);

	m_rotation = 0.0f;

	return true;
}

void Scene11::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene11::Update()
{
	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	model->m_shader.Use();

	float dt = m_engine->Get<Timer>()->FrameTime();

	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.m_position = rotation * light->m_transform.m_position;
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);
	model->m_shader.SetUniform("light.position", position);

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("lightPosition", position);
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene11::Shutdown()
{
}
