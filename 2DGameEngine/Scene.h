#pragma once
#include "GameObject.h"

class Scene {
public:	
	Scene() = default;
	~Scene() = default;

	void addObject(GameObject obj);
	void removeObject(int key);
	GameObject* getPointer(int key);
	void Draw();
};