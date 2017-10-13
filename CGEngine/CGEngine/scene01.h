#pragma once
#include "scene.h"

class Scene01 : public Scene
{
public:
	Scene01(Engine* engine) : Scene(engine) {};
	~Scene01();

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();
};

