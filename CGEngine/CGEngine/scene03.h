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
	GLuint m_vboHandles[3];
	GLuint m_vaoHandle;
};

