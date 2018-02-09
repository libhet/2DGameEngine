#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW3/glfw3.h>
#include "Shader.h"
#include "Render.h"
#include <exception>	// Throw if window not created?

//Add callback functional

class RenderOpenGL 
	: public _RenderImpl 
{
public:
	 RenderOpenGL() = default;
	~RenderOpenGL() = default;

	void	InitWindow(int wWidth, int wHeight, char const * wTitle) override;
	Image	LoadImageImpl(char const * filename) override;
	void	DrawImageImpl(Image const & img) override;
	void	DrawAnimationImpl(Animation & ani) override;

private:
	GLFWwindow	*_window;
	int			_wWidth;
	int			_wHeight;
	const char  *_wTitle;
	void(*key_callback)(GLFWwindow*, int, int, int, int);
};