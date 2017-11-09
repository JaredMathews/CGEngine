#pragma once
#include "object.h"
#include "material.h"
#include "shader.h"

class Renderable :
	public Object
{
public:
	Renderable(const std::string& name, Scene* scene) : Object(name, scene) {}
	~Renderable();

	void Update();
	void Render();

protected:
	Shader m_shaderProgram;
	Material m_material;
};

