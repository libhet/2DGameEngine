#pragma once
#include "Animation.h"

class GameObject {
public:
	union
	{
		Image img;
		Animation ani;
	} object;
	struct {
		float x;
		float y;
	} position;



	GameObject() = default;
	~GameObject();
};