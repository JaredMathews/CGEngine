#pragma once
#include "engine.h"
#include "shader.h"

class Object;

class Scene
{
public:
	Scene(Engine* engine) : m_engine(engine) {}
	virtual ~Scene() 
	{
		for (auto object : m_objects)
		{
			delete object;
		}
	}

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;

	void AddObject(Object* obj);

	template<typename T>
	T* GetObject(const std::string& name)
	{
		for each (auto obj in m_objects)
		{
			if (obj->m_name == name)
			{
				if (dynamic_cast<T*>(obj) != nullptr)
				{
					return dynamic_cast<T*>(obj);
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetObjects()
	{
		std::vector<T*> tempVec;
		for each (auto obj in m_objects)
		{
			if (dynamic_cast<T*>(obj) != nullptr)
			{
				tempVec.push_back(dynamic_cast<T*> (obj));
			}
		}
		return tempVec;
	}

public:
	Engine* m_engine;
	Shader m_shaderProgram;

protected:
	std::vector<Object*> m_objects;
};

