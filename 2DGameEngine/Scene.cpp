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

void Scene::Draw(GLFWwindow* _window)
{
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	for (auto obj : objects) {
		obj.second->Draw();
	}

	glfwSwapBuffers(_window);
	}
}
