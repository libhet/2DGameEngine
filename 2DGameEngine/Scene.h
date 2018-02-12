#pragma once
#include "GameObject.h"
#include "Render.h"
#include <unordered_map>
#include <thread>

class Scene  {
public:	
	Scene() = default;
	~Scene() = default;

	void addObject(std::string name, GameObject *obj);
	void removeObject(std::string key);
	GameObject* getPointer(std::string key);
	void Draw(_Render * render);

private:
	std::unordered_map<std::string, GameObject*> objects;
};