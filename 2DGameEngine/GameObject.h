#pragma once
#include "Animation.h"


class GameObject {
public:
	GameObject(float x,float y) {
		position.x = x;
		position.y = y;
	}
	GameObject(int x, int y) {
		pixelPosition.x = x;
		pixelPosition.y = y;
	}
	~GameObject() = default;

	void setpos(float x, float y);
	void setpos(int x, int y);

private:
	struct { float x; float y; }	position;
	struct { int x; int y; }		pixelPosition;
};

class GameObjectImage : GameObject {
public:

private:
	Image img;
};

class GameObjectAnimation : GameObject {
public:

private:
	Animation ani;
};