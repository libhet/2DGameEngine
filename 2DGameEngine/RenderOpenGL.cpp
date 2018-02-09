#include "RenderOpenGL.h"


void RenderOpenGL::InitWindow(int wWidth, int wHeight, char const * wTitle)
{
	_wWidth = wWidth;
	_wHeight = wHeight;
	_wTitle = wTitle;
		//Создание окна
			//Инициализация
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	

			_window = glfwCreateWindow(wWidth, wHeight, wTitle, nullptr, nullptr);
			if (_window == nullptr) {
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return;
			}
			glfwMakeContextCurrent(_window);
	
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW" << std::endl;
				return;
			}
	
			int width, height;
			glfwGetFramebufferSize(_window, &width, &height);
			glViewport(0, 0, width, height);
	
			//glfwSetKeyCallback(_window, key_callback);
			//Инициализация конец
	
			//Разрешить прозрачность
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Image RenderOpenGL::LoadImageImpl(char const * filename)
{
	return Image(filename);
}

void RenderOpenGL::DrawImageImpl(Image const & img)
{
	GLfloat y = 1*(float(img.getHeight()) / float(_wHeight));
	GLfloat x = 1*(float(img.getWidth()) / float(_wWidth));

		//Создание вершин
			GLfloat vertices[] = {
				// Positions     // Texture Coords
				 x,  y, 0.0f,    1.0f, 1.0f,	
				 x, -y, 0.0f,    1.0f, 0.0f,	
				-x, -y, 0.0f,    0.0f, 0.0f,	
				-x,  y, 0.0f,    0.0f, 1.0f		
			};
		GLuint indices[] = {
			0, 1, 3,  
			1, 2, 3    
		};
		//Создание вершин конец

		//Буферная магия
		GLuint VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);	
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	
		glBindVertexArray(VAO);	
	
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	
		glBindVertexArray(0);
		//Буферная магия
	//=============================================================

		Shader shaderProgram = Shader("vshader.glsl", "fshader.glsl");
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		//Запуск окна
		while (!glfwWindowShouldClose(_window))
		{
			//Ловим события
			glfwPollEvents();
	
			//Фоновый цвет
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
	
			//Отрисовка
			glBindTexture(GL_TEXTURE_2D, texture);
			shaderProgram.Use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
	
			glfwSwapBuffers(_window);
		}
	
	
		//Очистка ресурсов OpenGL
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	
		//Закрытие окна
		glfwTerminate();

}

