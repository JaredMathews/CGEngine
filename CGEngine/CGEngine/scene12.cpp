#include "stdafx.h"
#include "scene12.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "model.h"
#include "timer.h"

#define SHADOW_BUFFER_WIDTH	1024
#define SHADOW_BUFFER_HEIGHT 1024

Scene12::~Scene12()
{
}

bool Scene12::Initialize()
{
	GLuint depthTexture = Material::CreateDepthTexture(SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);

	m_depthShader = new Shader();
	m_depthShader->CompileShader("..\\Resources\\Shaders\\shadow_depth.vert.shader", GL_VERTEX_SHADER);
	m_depthShader->CompileShader("..\\Resources\\Shaders\\shadow_depth.frag.shader", GL_FRAGMENT_SHADER);
	m_depthShader->Link();

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	// light
	Light* light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(0.0f, 3.0f, 2.0f);
	light->ambient = glm::vec3(0.2f);
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.25f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_phong.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_phong.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.ambient", light->ambient);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\suzanne.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_material.AddTexture(depthTexture, GL_TEXTURE1);

	AddObject(model);

	model = new Model("floor", this);
	model->m_transform.m_scale = glm::vec3(8.0f);
	model->m_transform.m_position = glm::vec3(0.0f, -1.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_phong.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_phong.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.ambient", light->ambient);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\plane.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	model->m_material.AddTexture(depthTexture, GL_TEXTURE1);

	AddObject(model);

	model = new Model("debug", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.25f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_depth_debug.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\shadow_depth_debug.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.ambient", light->ambient);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\quad.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::TEXCOORD);

	model->m_material.AddTexture(depthTexture, GL_TEXTURE0);

	AddObject(model);

	m_rotation = 0.0f;

	m_depthBuffer = Material::CreateDepthbuffer(depthTexture, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);

	return true;
}

void Scene12::Render()
{
	glViewport(0, 0, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);

	m_depthShader->Use();

	auto model = GetObject<Model>("model");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();

	model = GetObject<Model>("floor");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//model = GetObject<Model>("debug");
	//model->Render();

	auto renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene12::Update()
{
	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	model->m_shader.Use();

	float dt = m_engine->Get<Timer>()->FrameTime();

	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.m_position = rotation * light->m_transform.m_position;

	glm::mat4 mxLightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f); glm::mat4 mxLightView = glm::lookAt(light->m_transform.m_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mxVP = mxLightProjection * mxLightView;

	m_depthShader->Use();
	m_depthShader->SetUniform("mxLVP", mxVP);

	glm::vec4 lightPosition = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);

	glm::mat4 mxBias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", lightPosition);
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		glm::mat4 mxBVP = mxBias * mxVP * mxModel;
		model->m_shader.SetUniform("mxMLP", mxBVP);
	}


	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene12::Shutdown()
{
}
