#include <iostream>

using namespace std;

#include "RenderOpenGL.h"
#include "GameObject.h"

int main() {

	Animation ani("animation/anim", "png",1 ,9);
	
	Render OpenGL(&RenderOpenGL());
	OpenGL.InitWindow(256, 256, "Test");

	OpenGL.DrawAnimation(ani);
	return 0;

}


//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//int main() {
//
//	//Создание окна
//		//Инициализация
//		glfwInit();
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//		int wWidth = 800;
//		int wHeight = 800;
//		char *wTitle = "Window";
//
//		GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, wTitle, nullptr, nullptr);
//		if (window == nullptr) {
//			std::cout << "Failed to create GLFW window" << std::endl;
//			glfwTerminate();
//			return -1;
//		}
//		glfwMakeContextCurrent(window);
//
//		glewExperimental = GL_TRUE;
//		if (glewInit() != GLEW_OK)
//		{
//			std::cout << "Failed to initialize GLEW" << std::endl;
//			return -1;
//		}
//
//		int width, height;
//		glfwGetFramebufferSize(window, &width, &height);
//		glViewport(0, 0, width, height);
//
//		glfwSetKeyCallback(window, key_callback);
//		//Инициализация конец
//
//		//Разрешить прозрачность
//		glEnable(GL_ALPHA_TEST);
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//
////=============================================================
//	//Создание вершин
//		GLfloat vertices[] = {
//			// Positions           // Texture Coords
//			0.5f,  0.5f, 0.0f,     1.0f, 1.0f,			// Top Right
//			0.5f, -0.5f, 0.0f,     1.0f, 0.0f,			// Bottom Right
//			-0.5f, -0.5f, 0.0f,    0.0f, 0.0f,			// Bottom Left
//			-0.5f,  0.5f, 0.0f,    0.0f, 1.0f			// Top Left 
//		};
//	GLuint indices[] = {  // Помните, что мы начинаем с 0!
//		0, 1, 3,   // Первый треугольник
//		1, 2, 3    // Второй треугольник
//	};
//	//Создание вершин конец
//
//
//	////Создание вершин
//	//GLuint INTvertices[] = {
//	//	// Positions           // Texture Coords
//	//	200,  200, 0,     10, 10,			// Top Right
//	//	200, -50, 0,     10, 0,			// Bottom Right
//	//	-80, -200, 0,    0, 0,			// Bottom Let
//	//	-200,  200, 0,    0, 10			// Top Let 
//	//};
//	//GLuint INTindices[] = {  // Помните, что мы начинаем с 0!
//	//	0, 1, 3,   // Первый треугольник
//	//	1, 2, 3    // Второй треугольник
//	//};
//	////Создание вершин конец
//
//
//	//Буферная магия
//	GLuint VBO, VAO, EBO;	//Для идентификаторов
//	glGenVertexArrays(1, &VAO);	//Выделяет N идентефикаторов и записыват во второй параметр
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);	//Говорим что VAO это Vertex Array
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	// TexCoord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	//// Position attribute
//	//glVertexAttribPointer(0, 3, GL_UNSIGNED_INT, GL_TRUE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	//glEnableVertexAttribArray(0);
//
//	//// TexCoord attribute
//	//glVertexAttribPointer(2, 2, GL_UNSIGNED_INT, GL_TRUE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	//glEnableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//	//Буферная магия
////=============================================================
//	
//
//	Shader shaderProgram = Shader("vshader.glsl", "fshader.glsl");
//
//	////Текстура
//	//GLuint texture;
//	//glGenTextures(1, &texture);
//	//glBindTexture(GL_TEXTURE_2D, texture);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// Set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//int width2, height2, chan;
//	//unsigned char* image = SOIL_load_image("test4.png", &width2, &height2, &chan, SOIL_LOAD_RGBA);
//	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//SOIL_free_image_data(image);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//
//	Image img1("test4.png");
//
//	//Запуск окна
//	while (!glfwWindowShouldClose(window))
//	{
//		//Ловим события
//		glfwPollEvents();
//
//		//Фоновый цвет
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//Отрисовка
//		glBindTexture(GL_TEXTURE_2D, img1.getTexture());
//		shaderProgram.Use();
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//
//
//	//Очистка ресурсов OpenGL
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	//Закрытие окна
//	glfwTerminate();
//
//	return 0;
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	std::cout << key << std::endl;
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}
