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
//
//class OGL_GameObjectImage : public GameObject {
//public:
//	OGL_GameObjectImage() = delete;
//	OGL_GameObjectImage(Image const * _img, float x, float y);
//	~OGL_GameObjectImage();
//
//	void Draw() override;
//
//protected:
//	void generateBuffers(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO);
//	void bindObject(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO, GLfloat *vertices, int sizeofvertices, GLuint *indices, int sizeofindices);
//	void bindTexture(GLuint texture, Image const & img);
//	void drawElement(int N, GLuint texture, Shader *shaderProgram, GLuint *VAO, GLuint *VBO, GLfloat *vertices, int sizeofvertices);
//
//private:
//	Image const * img;
//	GLfloat vertices[20] = {
//		0, 0, 0.0f,    1.0f, 0.0f,
//		0, 0, 0.0f,    1.0f, 1.0f,
//		0, 0, 0.0f,    0.0f, 1.0f,
//		0, 0, 0.0f,    0.0f, 0.0f
//	};
//	GLuint indices[6] = { 0, 1, 3, 1, 2, 3 };
//	GLuint VBO, VAO, EBO, texture;
//	Shader shaderProgram;
//};
//
//class GameObjectImage 
//	: public GameObject
//{
//public:
//	GameObjectImage() = default;
//	GameObjectImage(float x, float y)
//		: GameObject(x,y) {}
//	~GameObjectImage() = default;
//
//private:
//	Image* img;
//};
//
//class GameObjectAnimation 
//	: public GameObject {
//public:
//
//private:
//	Animation ani;
//};