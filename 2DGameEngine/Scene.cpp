#include "Scene.h"

void Scene::addObject(GameObject obj)
{
}

void Scene::removeObject(std::string key)
{
}

GameObject * Scene::getPointer(std::string key)
{
	return nullptr;
}

void Scene::Draw()
{
	for (auto obj : objects) {
		//obj.second->init();
	}
}
