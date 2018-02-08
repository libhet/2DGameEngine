#pragma once
#include <string>
#include <vector>
#include <SOIL\SOIL.h>
#include <GL\glew.h>
#include <GLFW3\glfw3.h>

// Содержит квадрат из вершин
// На который отображается текстура
// Возможность корректировать высоту и ширину
// В методе отрисовки все данные для отрисовки помещаются в буфер 

class Image {
private:
	GLuint texture;
	std::vector<unsigned int> vertices;
	unsigned char* image;
	int channels;
	int width;
	int height;
public:
	Image(std::string _filename) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		image = SOIL_load_image(_filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	~Image() = default;
	void Draw() {

	}
	GLuint getTexture() {
		return texture;
	}
};
