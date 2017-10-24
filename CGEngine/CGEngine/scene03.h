#pragma once
#include "scene.h"
class Scene03 :
	public Scene
{
public:
	Scene03(Engine* engine) : Scene(engine) {};
	~Scene03();

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

	object m_cube;
	light m_light;

	float m_rotation;
};

