#pragma once
#include "Render.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW3/glfw3.h>
#include "Shader.h"
#include <exception>

// Конкретная реализация методов рендера для OpenGL
//ДОБАВИТЬ OVERRID



class RenderOpenGL : public _RenderImpl {
private:
	GLFWwindow* window;
	int wWidth;
	int wHeight; 
	const char* wTitle;
	void(*key_callback)(GLFWwindow*, int, int, int, int);
public:
	RenderOpenGL() = default;
	virtual ~RenderOpenGL() = default;

	virtual void InitWindow(int wWidth, int wHeight, char const * wTitle);
	virtual Image LoadImageImpl(char const * filename) ;
	virtual void DrawImageImpl(Image const & img) override;
};