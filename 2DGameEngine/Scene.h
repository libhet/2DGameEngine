#pragma once
#include "GameObject.h"
#include <map>

class Scene {
public:	
	Scene() = default;
	~Scene() = default;

	void addObject(GameObject obj);
	void removeObject(std::string key);
	GameObject* getPointer(std::string key);
	void Draw();

private:
	std::map<std::string, GameObject*> objects;
};