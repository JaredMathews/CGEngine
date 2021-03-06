#include "stdafx.h"
#include "engine.h"
#include "renderer.h"
#include "glm\vec3.hpp"
#include "scene01.h"
#include "scene02.h"
#include "scene03.h"
#include "scene04.h"
#include "scene05.h"
#include "scene06.h"
#include "scene07.h"
#include "scene08.h"
#include "scene09.h"
#include "scene10.h"
#include "scene11.h"
#include "scene12.h"

int main()
{
	std::shared_ptr<Engine> engine(new Engine);
	if (!engine->Initialize())
	{
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	std::shared_ptr<Scene> scene(new Scene12(engine.get()));
	if (!scene->Initialize())
	{
		scene->Shutdown();
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(engine->Get<Renderer>()->m_window))
	{
		engine->Update();
		scene->Update();
		scene->Render();
	}

	scene->Shutdown();
	engine->Shutdown();

    return 0;
}

