#include "GameObject.h"

//OGL_GameObjectImage::OGL_GameObjectImage(Image const *_img, float _x, float _y)
//	:img(_img),GameObject(_x,_y),shaderProgram("vshader.glsl", "fshader.glsl")
//{
//	//verybad1000
//	GLfloat y = 1 * (float(img->getHeight()) / float(1000));
//	GLfloat x = 1 * (float(img->getWidth()) / float(1000));
//
//	vertices[0] = x;
//	vertices[1] = y;
//	vertices[5] = x;
//	vertices[6] = -y;
//	vertices[10] = -x;
//	vertices[11] = -y;
//	vertices[15] = -x;
//	vertices[16] = y;
//
//	generateBuffers(1, &VBO, &VAO, &EBO);
//	bindObject(0, &VAO, &VBO, &EBO, vertices, sizeof(vertices), indices, sizeof(indices));
//	glGenTextures(1, &texture);
//	bindTexture(texture, *img);
//}
//
//OGL_GameObjectImage::~OGL_GameObjectImage()
//{
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glDeleteTextures(1, &texture);
//}
//
//void OGL_GameObjectImage::Draw()
//{
//	drawElement(0, texture, &shaderProgram, &VAO, &VBO, vertices, sizeof(vertices));
//}
//
//void OGL_GameObjectImage::generateBuffers(int N, GLuint * VAO, GLuint * VBO, GLuint * EBO)
//{
//	glGenVertexArrays(N, VAO);
//	glGenBuffers(N, VBO);
//	glGenBuffers(N, EBO);
//}
//
//void OGL_GameObjectImage::bindObject(int N, GLuint * VAO, GLuint * VBO, GLuint * EBO, GLfloat * vertices, int sizeofvertices, GLuint * indices, int sizeofindices)
//{
//	glBindVertexArray(VAO[N]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[N]);
//	glBufferData(GL_ARRAY_BUFFER, sizeofvertices, vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[N]);
//	auto a = sizeof(indices);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofindices, indices, GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	// TexCoord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//}
//
//void OGL_GameObjectImage::bindTexture(GLuint texture, Image const & img)
//{
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//void OGL_GameObjectImage::drawElement(int N, GLuint texture, Shader * shaderProgram, GLuint * VAO, GLuint * VBO, GLfloat * vertices, int sizeofvertices)
//{
//	glBindTexture(GL_TEXTURE_2D, texture);
//	shaderProgram->Use();
//	glBindVertexArray(VAO[N]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[N]);
//	glBufferData(GL_ARRAY_BUFFER, sizeofvertices, vertices, GL_STATIC_DRAW);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}
