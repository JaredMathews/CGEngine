#pragma once
#include "scene.h"

class Scene02 : public Scene
{
public:
	Scene02(Engine* engine) : Scene(engine) {};
	~Scene02();

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();

private:
	GLuint m_vboHandles[3];
	GLuint m_vaoHandle;
	GLuint m_shaderProgram;
	float m_cursorSize = .15f;
	float m_x;
	float m_y;
};
