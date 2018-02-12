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
			glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
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

void RenderOpenGL::DrawAnimationImpl(Animation & ani)
{
	int ani_height= ani.begin()->getHeight();
	int ani_width = ani.begin()->getWidth();
	GLfloat y = 1 * (float(ani_height) / float(_wHeight));
	GLfloat x = 1 * (float(ani_width) / float(_wWidth));

	//Алгоритм перемещения.
	//Когда нажимается кнопка, какая то глобальная переменная равна 1
	// умножается на скорость премещения и плюсуется
	// когда кнопка отжимается то переменная равна 0
	// и объект остается сдвинут но не перемещается


	// У каждого изображения есть массив вершин 
	//Создание вершин
	GLfloat vertices[] = {
		// Positions     // Texture Coords
		x,  y, 0.0f,    1.0f, 1.0f,
		x, -y, 0.0f,    1.0f, 0.0f,
		-x, -y, 0.0f,   0.0f, 0.0f,
		-x,  y, 0.0f,   0.0f, 1.0f
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
	GLuint *textures = new GLuint [ani.size()];

	// Для анимации создается несолько объектов OpenGL
	glGenTextures(ani.size(), textures);

	//Настройка текстуры
	for (int i = 0; i < ani.size(); ++i) {

		//Функция настройки текстуры.
		//Принимает указатель на данные изображения
		//ширину и высоту
		//
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ani_width, ani_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ani[i].getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	int i = 0;		//Тут нужен массив интов для каждой анимации
	//Запуск окна
	while (!glfwWindowShouldClose(_window))
	{
		//Ловим события
		glfwPollEvents();

		//Фоновый цвет
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Отрисовка	//В цикле вызывать функцию которая описана ниже
				//Написать функцию которая биндит текстуру использует шейдер. 
				//биндит VAO рисует и отбиндивает
				//принимает текстуру инт, вао инт
		//Для каждого объекта нужен свой буфер
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			shaderProgram.Use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		glfwSwapBuffers(_window);

		Sleep(1000/50);
		//цикл который пробегается по массиву интов 
		//для всех анимаций в сцене

		i == ani.size() ? i = 0 : i++;
	}

	//Очистка ресурсов OpenGL
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete[] textures;
	//Закрытие окна
	glfwTerminate();

}

void RenderOpenGL::DrawImageImpl2(Image const & img)
{

	GLfloat y = 1 * (float(img.getHeight()) / float(_wHeight));
	GLfloat x = 1 * (float(img.getWidth()) / float(_wWidth));

	GLfloat vertices[] = {
		x,  y, 0.0f,    1.0f, 0.0f,
		x, -y, 0.0f,    1.0f, 1.0f,
		-x, -y, 0.0f,    0.0f, 1.0f,
		-x,  y, 0.0f,    0.0f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VBO, VAO, EBO;
	generateBuffers(1, &VBO, &VAO, &EBO);
	bindObject(0, &VAO, &VBO, &EBO, vertices, sizeof(vertices), indices, sizeof(indices));
	Shader shaderProgram = Shader("vshader.glsl", "fshader.glsl");
	GLuint texture;
	glGenTextures(1, &texture);
	bindTexture(texture, img);

	while (!glfwWindowShouldClose(_window))
	{

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//moveSquare(&positionX, &positionY, vertices[currentObject], &speed);

		drawElement(0, texture, &shaderProgram, &VAO, &VBO, vertices, sizeof(vertices));

		glfwSwapBuffers(_window);


	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	//	glfwTerminate();
}

void RenderOpenGL::generateBuffers(int N, GLuint * VAO, GLuint * VBO, GLuint * EBO)
{
	glGenVertexArrays(N, VAO);
	glGenBuffers(N, VBO);
	glGenBuffers(N, EBO);
}

void RenderOpenGL::bindObject(int N, GLuint * VAO, GLuint * VBO, GLuint * EBO, GLfloat * vertices, int sizeofvertices, GLuint * indices, int sizeofindices)
{
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

void RenderOpenGL::bindTexture(GLuint texture, Image const & img)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderOpenGL::drawElement(int N, GLuint texture, Shader * shaderProgram, GLuint * VAO, GLuint * VBO, GLfloat * vertices, int sizeofvertices)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	shaderProgram->Use();
	glBindVertexArray(VAO[N]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[N]);
	glBufferData(GL_ARRAY_BUFFER, sizeofvertices, vertices, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void RenderOpenGL::addToRender(Image const & img) 
{
	GLfloat y = 1 * (float(img.getHeight()) / float(_wHeight));
	GLfloat x = 1 * (float(img.getWidth()) / float(_wWidth));

	GLfloat vertices[] = {
		x,  y, 0.0f,    1.0f, 0.0f,
		x, -y, 0.0f,    1.0f, 1.0f,
		-x, -y, 0.0f,    0.0f, 1.0f,
		-x,  y, 0.0f,    0.0f, 0.0f
	};
		vertices[0] = x;
		vertices[1] = y;
		vertices[5] = x;
		vertices[6] = -y;
		vertices[10] = -x;
		vertices[11] = -y;
		vertices[15] = -x;
		vertices[16] = y;

	m_vertices.push_back(vertices);

	GLuint VBO, VAO, EBO;
	generateBuffers(1, &VBO, &VAO, &EBO);
	bindObject(0, &VAO, &VBO, &EBO, *std::prev(m_vertices.end()), sizeof(vertices), m_indices, sizeof(m_indices));
	m_VBO.push_back(VBO);
	m_VAO.push_back(VAO);
	m_EBO.push_back(EBO);
	GLuint texture;
	glGenTextures(1, &texture);
	bindTexture(texture, img);
	m_texture.push_back(texture);
}

