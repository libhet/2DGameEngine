#include "RenderOpenGL.h"


void RenderOpenGL::InitWindow(int wWidth, int wHeight, char const * wTitle)
{
		//Создание окна
			//Инициализация
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
			//int wWidth = 800;
			//int wHeight = 800;
			//char *wTitle = "Window";
	
			GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, wTitle, nullptr, nullptr);
			if (window == nullptr) {
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return;
			}
			glfwMakeContextCurrent(window);
	
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW" << std::endl;
				return;
			}
	
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
	
			glfwSetKeyCallback(window, key_callback);
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

}

