#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW3/glfw3.h>
#include "Shader.h"
#include "Render.h"
#include <exception>	// Throw if window not created?
#include <chrono>
#include <thread>
#define Sleep(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms));

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
	void	DrawImageImpl2(Image const & img) override;
	void	addToRender(Image const & img) override;

protected:
	void	generateBuffers(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO);
	void	bindObject(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO, GLfloat *vertices, int sizeofvertices, GLuint *indices, int sizeofindices);
	void	bindTexture(GLuint texture, Image const & img);
	void	drawElement(int N, GLuint texture, Shader *shaderProgram, GLuint *VAO, GLuint *VBO, GLfloat *vertices, int sizeofvertices);


private:
	GLFWwindow	*_window;
	int			_wWidth;
	int			_wHeight;
	const char  *_wTitle;
	void(*key_callback)(GLFWwindow*, int, int, int, int);

	std::vector<GLfloat*> m_vertices;
	GLuint m_indices[6] = { 0, 1, 3, 1, 2, 3 };
	//Shader m_shaderProgram;
	std::vector<GLuint> m_VBO;
	std::vector<GLuint> m_VAO;
	std::vector<GLuint> m_EBO;
	std::vector<GLuint> m_texture;
};