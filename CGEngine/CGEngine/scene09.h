#pragma once
#include "scene.h"
#include "material.h"
#include "camera.h"
#include "mesh.h"

class Scene09 :
	public Scene
{
public:
	Scene09(Engine* engine) : Scene(engine) {};
	~Scene09();

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();

private:
	struct object
	{
		// id / handles
		GLuint shaderProgram;
		GLuint vaoHandle;

		// transforms
		GLint mxModelViewUniform;
		GLint mxMVPUniform;
		GLint mxNormalUniform;

		// material
		GLint ambientMaterialUniform;
		GLint diffuseMaterialUniform;
		GLint specularMaterialUniform;
	};

	struct light
	{
		GLint positionUniform;
		GLint colorUniform;
	};

private:
	GLuint m_vboHandles[3];
	GLuint m_vaoHandle;

	GLuint m_texture[2];

	object m_cube;
	light m_light;

	float m_rotation;

	Material m_material;

	Camera* m_camera;
};

