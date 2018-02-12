#include "Scene.h"


void Scene::addObject(std::string name, GameObject *obj)
{
	objects.insert({ name, obj });
}

void Scene::removeObject(std::string key)
{
	objects.erase(key);
}

GameObject * Scene::getPointer(std::string key)
{
	return objects[key];
}

void Scene::Draw(_Render * render)
{
	int size = objects.size();
	GLfloat *x = new GLfloat(size);
	GLfloat *y = new GLfloat(size);
	for (int i = 0; i < size; ++i) {

	}

	std::vector<std::thread> threads;
	threads.reserve(size);

	int i = 0;
	for (auto obj : objects) {
	//	threads.push_back(std::thread(&RenderOpenGL::DrawImageImpl2, this, obj.second->getImg()[0]));
	}

}

