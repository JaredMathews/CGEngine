#include "stdafx.h"
#include "engine.h"
#include "renderer.h"
#include "glm\vec3.hpp"
#include "scene01.h"

int main()
{
	std::shared_ptr<Engine> engine(new Engine);
	if (!engine->Initialize())
	{
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	std::shared_ptr<Scene> scene(new Scene01(engine.get()));
	if (!scene->Initialize())
	{
		scene->Shutdown();
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	GLuint program = engine->Get<Renderer>()->CreateShaderProgram("..\\Resources\\Shaders\\basic.vert", "..\\Resources\\Shaders\\basic.frag");

	while (!glfwWindowShouldClose(engine->Get<Renderer>()->m_window))
	{
		engine->Update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render code
		glBindVertexArray(vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(engine->Get<Renderer>()->m_window);
	}
	engine->Shutdown();

    return 0;
}

