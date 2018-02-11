#pragma once
#include "Animation.h"
#include "RenderOpenGL.h"

class GameObject {
public:
	GameObject() = default;
	GameObject(float x,float y) {
		position.x = x;
		position.y = y;
	}
	GameObject(int x, int y) {
		pixelPosition.x = x;
		pixelPosition.y = y;
	}
	~GameObject() = default;

	virtual void Draw() {}

	void setpos(float x, float y);
	void setpos(int x, int y);

private:
	struct { float x; float y; }	position;
	struct { int x; int y; }		pixelPosition;
};

class OGL_GameObjectImage : public GameObject {
public:
	OGL_GameObjectImage() = delete;
	OGL_GameObjectImage(Image const * _img, float x, float y);
	~OGL_GameObjectImage();

	void Draw() override;

protected:
	void generateBuffers(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO);
	void bindObject(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO, GLfloat *vertices, int sizeofvertices, GLuint *indices, int sizeofindices);
	void bindTexture(GLuint texture, Image const & img);
	void drawElement(int N, GLuint texture, Shader *shaderProgram, GLuint *VAO, GLuint *VBO, GLfloat *vertices, int sizeofvertices);

private:
	Image const * img;
	GLfloat vertices[20] = {
		0, 0, 0.0f,    1.0f, 0.0f,
		0, 0, 0.0f,    1.0f, 1.0f,
		0, 0, 0.0f,    0.0f, 1.0f,
		0, 0, 0.0f,    0.0f, 0.0f
	};
	GLuint indices[6] = { 0, 1, 3, 1, 2, 3 };
	GLuint VBO, VAO, EBO, texture;
	Shader shaderProgram;
};

class GameObjectAnimation : GameObject {
public:

private:
	Animation ani;
};