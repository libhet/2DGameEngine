#include <iostream>

using namespace std;

#include "RenderOpenGL.h"
#include "GameObject.h"
#include "Scene.h"

//int main() {
//
//	//Animation ani("animation/anim", "png",1 ,9);
//	
//	Render OpenGL(&RenderOpenGL());
//	OpenGL.InitWindow(800, 800, "Test");
//	//OpenGL.DrawImage(Image("ship.png"));
//	GameObject a(Image("test4.png"), 1, 1);
//	GameObject b(Image("ship.png"), 1, 1);
//	GameObject c(Image("test.png"), 1, 1);
//	Scene sc;
//	sc.addObject("a", &a);
//	sc.addObject("b", &b);
//	sc.addObject("c", &c);
//
//	sc.Draw(&OpenGL);
//
//	return 0;
//
//}

float positionX = 0;
float positionY = 0;
float speed = 0.002;
int currentObject = 0;
int maxObjectNumber = 1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void moveSquare(float *_positionX, float *_positionY, float *v_array, float *speed, int shift = 5) {
	v_array[0] += *_positionX * *speed;
	v_array[1] += *_positionY * *speed;

	v_array[0 + shift] += *_positionX * *speed;
	v_array[1 + shift] += *_positionY * *speed;

	v_array[0 + 2 * shift] += *_positionX * *speed;
	v_array[1 + 2 * shift] += *_positionY * *speed;

	v_array[0 + 3 * shift] += *_positionX * *speed;
	v_array[1 + 3 * shift] += *_positionY * *speed;
}

void generateBuffers(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO) {
	glGenVertexArrays(N, VAO);
	glGenBuffers(N, VBO);
	glGenBuffers(N, EBO);
}

void bindObject(int N, GLuint *VAO, GLuint *VBO, GLuint *EBO, GLfloat *vertices, int sizeofvertices, GLuint *indices, int sizeofindices) {
	glBindVertexArray(VAO[N]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[N]);
	glBufferData(GL_ARRAY_BUFFER, sizeofvertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[N]);
	auto a = sizeof(indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofindices, indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void bindTexture(GLuint texture, Image img) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawElement(int N, GLuint texture, Shader *shaderProgram, GLuint *VAO, GLuint *VBO, GLfloat *vertices, int sizeofvertices) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shaderProgram->Use();
	glBindVertexArray(VAO[N]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[N]);
	glBufferData(GL_ARRAY_BUFFER, sizeofvertices, vertices, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void test(GLFWwindow* window, int N, GLuint texture, Shader *shaderProgram, GLuint *VAO, GLuint *VBO, GLfloat *vertices, int sizeofvertices) {
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		moveSquare(&positionX, &positionY, vertices, &speed);

		drawElement(N, texture, shaderProgram, VAO, VBO, vertices, sizeof(vertices));

		glfwSwapBuffers(window);
	}
}

int main() {

	//Создание окна
		//Инициализация
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int wWidth = 800;
	int wHeight = 800;
	char *wTitle = "Window";

	GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, wTitle, nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	//glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);

	//Разрешить прозрачность
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//=============================================================

	GLfloat vertices[2][20] = {{
		// Positions           // Texture Coords
		5.5f,  1.5f*100, 0.0f,     3.0f, 100.0f,			// Top Right
		5.5f, -1.5f*100, 0.0f,     3.0f, 0.0f,			// Bottom Right
		-5.5f, -1.5f*100, 0.0f,    0.0f, 0.0f,			// Bottom Left
		-5.5f,  1.5f*100, 0.0f,    0.0f, 100.0f			// Top Left 
	},
	{
		// Positions           // Texture Coords
		0.17875f,  0.32f, 0.0f,     1.0f, 0.0f,			// Top Right
		0.17875f, -0.32f, 0.0f,     1.0f, 1.0f,			// Bottom Right
		-0.17875f, -0.32f, 0.0f,    0.0f, 1.0f,			// Bottom Left
		-0.17875f,  0.32f, 0.0f,    0.0f, 0.0f			// Top Left 
	}
};
	GLuint indices[] = {  // Помните, что мы начинаем с 0!
		0, 1, 3,   // Первый треугольник
		1, 2, 3    // Второй треугольник
	};

	GLuint VBO[10], VAO[10], EBO[10];
	generateBuffers(2, VBO, VAO, EBO);

	bindObject(0, VAO, VBO, EBO, vertices[0], sizeof(vertices[0]), indices, sizeof(indices));
	bindObject(1, VAO, VBO, EBO, vertices[1], sizeof(vertices[1]), indices, sizeof(indices));

	Shader shaderProgram = Shader("vshader.glsl", "fshader.glsl");

	GLuint texture[2];
	glGenTextures(2, texture);
	bindTexture(texture[0], Image("space.png"));
	bindTexture(texture[1], Image("ship.png"));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		moveSquare(&positionX, &positionY, vertices[currentObject], &speed);

		drawElement(0, texture[0], &shaderProgram, VAO,VBO,vertices[0],sizeof(vertices[0]));

		drawElement(1, texture[1], &shaderProgram, VAO, VBO, vertices[1], sizeof(vertices[1]));

		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, EBO);

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		positionY = 1;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		positionY = 0;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		positionY = -1;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		positionY = 0;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		positionX = 1;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		positionX = 0;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		positionX = -1;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		positionX = 0;
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		speed += 0.0005;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		speed -= 0.0005;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		currentObject == maxObjectNumber?currentObject = 0:currentObject++;
	}
}
