#include <iostream>
#include <thread>


#include "RenderOpenGL.h"
#include "GameObject.h"
#include "Scene.h"



int main() {

	Animation ani("animation/anim", "png",1 ,9);

	std::cout << "Close the window to see animation" << std::endl;

	Render OpenGL(&RenderOpenGL());
	OpenGL.InitWindow(800, 800, "Image");
	OpenGL.DrawImage(Image("ship.png"));

	OpenGL.InitWindow(800, 800, "Animation");
	OpenGL.DrawAnimation(ani);

	return 0;

}