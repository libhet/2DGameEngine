#pragma once
#include "Animation.h"
#include "RenderOpenGL.h"

class GameObject {
public:
	GameObject() = default;
	GameObject(Image img, float x,float y) {
		position.x = x;
		position.y = y;
		imgs.push_back(img);
	}
	~GameObject() = default;

	size_t size() const {
		return imgs.size();
	}
	Image const * getImg() const  {
		return imgs.data();
	}
	void setpos(float x, float y) {
		position.x = x;
		position.y = y;
	}

private:
	std::vector<Image> imgs;
	struct { float x; float y; }	position;
};
