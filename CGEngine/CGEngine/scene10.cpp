#include "stdafx.h"
#include "scene10.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "model.h"
#include "timer.h"

Scene10::~Scene10()
{
}

bool Scene10::Initialize()
{
	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	// model
	auto model = new Model("skybox", this);
	model->m_transform.m_scale = glm::vec3(20.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	std::vector<std::string> suffixes = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
	model->m_material.LoadTextureCube("..\\Resources\\Textures\\lancellotti", suffixes, "jpg", GL_TEXTURE0);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\cube.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);

	GLuint skyboxIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "skybox");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &skyboxIndex);

	AddObject(model);

	model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\reflection.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	//suffixes = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
	//model->m_material.LoadTextureCube("..\\Resources\\Textures\\lancellotti", suffixes, "jpg", GL_TEXTURE0);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);

	skyboxIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "reflection");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &skyboxIndex);

	AddObject(model);

	return true;
}

void Scene10::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_CULL_FACE);

	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene10::Update()
{
	auto camera = GetObject<Camera>("camera");

	auto model = GetObject<Model>("model");
	float dt = m_engine->Get<Timer>()->FrameTime();
	model->m_transform.m_rotation = glm::quat(glm::vec3(0.0, dt, 0.0f)) * model->m_transform.m_rotation;

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		model->m_shader.Use();
		model->m_shader.SetUniform("mxModel", mxModel);
		model->m_shader.SetUniform("cameraWorldPosition", camera->m_transform.m_position);
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene10::Shutdown()
{
}
