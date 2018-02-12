#pragma once
#include "Render.h"
#include "Scene.h"

class Engine {
public:
	Engine() = default;
	~Engine() = default;

	void Draw();
private:
	Render *render;
	Scene *main_scene;
};