#pragma once
#include "GameObject.h"
#include <unordered_map>

class Scene {
public:	
	Scene() = default;
	~Scene() = default;

	void addObject(std::string name, GameObject *obj);
	void removeObject(std::string key);
	GameObject* getPointer(std::string key);
	void Draw(GLFWwindow* window);

private:
	std::unordered_map<std::string, GameObject*> objects;
};