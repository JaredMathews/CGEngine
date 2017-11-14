#include "stdafx.h"
#include "scene06.h"
#include "glm\vec3.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "renderer.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "model.h"

Scene06::~Scene06()
{
}

bool Scene06::Initialize()
{
	// light
	Light* light = new Light("light", this);
	light->m_transform.m_position = glm::vec3(2.0f, 2.0f, 2.0f);
	light->ambient = glm::vec3(0.2f);
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);

	// model
	auto model = new Model("model", this);
	model->m_transform.m_scale = glm::vec3(1.0f);
	model->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	model->m_shader.CompileShader("..\\Resources\\Shaders\\texture_phong.vert.shader", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("..\\Resources\\Shaders\\texture_phong_specular_fog.frag.shader", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 128.0f;
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	model->m_material.LoadTexture2D("..\\Resources\\Textures\\crate_specular.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.ambient", light->ambient);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	float distanceMin = 1.0f;
	float distanceMax = 20.0f;
	glm::vec3 fogColor = glm::vec3(0.0f, 0.0f, 0.75f);
	model->m_shader.SetUniform("fog.distanceMin", distanceMin);
	model->m_shader.SetUniform("fog.distanceMax", distanceMax);
	model->m_shader.SetUniform("fog.color", fogColor);

	model->m_mesh.Load("..\\Resources\\ObjFiles\\cube.obj");
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	AddObject(model);

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	return true;
}

void Scene06::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene06::Update()
{
	//Get the objects from the scene that we need to update
	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	//Transform the light position to put it into view space
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.m_position, 1.0f);
	//Set the model shader as current
	model->m_shader.Use();
	//Set the uniforms of the model shader
	model->m_shader.SetUniform("light.position", position);

	//This gets all objects in the scene and calls Update on each of them
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene06::Shutdown()
{
}
