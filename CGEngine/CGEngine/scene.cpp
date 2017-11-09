#include "stdafx.h"
#include "scene.h"
#include "object.h"

void Scene::AddObject(Object * obj)
{
	m_objects.push_back(obj);
}
