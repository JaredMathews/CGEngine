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

	virtual void Render() = 0;
};

