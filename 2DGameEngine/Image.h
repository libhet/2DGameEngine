#pragma once
#include <string>
#include <SOIL\SOIL.h>

#include <iostream>

// Содержит квадрат из вершин
// На который отображается текстура
// Возможность корректировать высоту и ширину
// В методе отрисовки все данные для отрисовки помещаются в буфер 

class Image {
public:
	Image(std::string _filename) :  name(_filename)
	{
		//glGenTextures(1, &texture);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		image = SOIL_load_image(_filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	~Image() {
		SOIL_free_image_data(image);
	}

	Image(Image const& img)
		: name(img.name), 
		  image(new unsigned char[img.width*img.height*img.channels]),
		  width(img.width),
		  height(img.height),
		  channels(img.channels) 
	{
		std::cout << "copy" << endl;
		for (size_t i = 0; i < img.width*img.height*img.channels; i++) {
			image[i] = img.image[i];
		}
	}
	Image & operator=(Image const& img) {
		if (this != &img) {
			SOIL_free_image_data(image);
			name = img.name;
			image = new unsigned char[img.width*img.height*img.channels];
			width = img.width;
			height = img.height;
			channels = img.channels;
			for (size_t i = 0; i < img.width*img.height*img.channels; i++) {
				image[i] = img.image[i];
			}
		}
		return *this;
	}

	Image(Image && img)  
		: name(img.name),
		  image(img.image),
		  width(img.width),
		  height(img.height),
		  channels(img.channels)
	{
		std::cout << "move" << endl;
		img.image = nullptr;
	}
	Image & operator=(Image && img) {
		SOIL_free_image_data(image);
		name = img.name;
		image = img.image;
		width = img.width;
		height = img.height;
		channels = img.channels;
		img.image = nullptr;
		return *this;
	}

	unsigned char* getData() {
		return image;
	}
	int getChannels() {
		return channels;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	string getName() {
		return name;
	}
	size_t size() {
		return width*height*channels;
	}
	//GLuint getTexture() {
	//	return texture;
	//}

private:
	std::string name;
	unsigned char* image;
	int width;
	int height;
	int channels;
};
