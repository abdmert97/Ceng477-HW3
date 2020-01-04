#ifndef OPENGL_H
#define OPENGL_H
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using  namespace glm;
using namespace std;


class OpenGL
{
public:
	 unsigned int texture;
	 unsigned int VAO;
	 unsigned int VBO, EBO;
	 GLFWwindow* openWindow(const char* windowName, int width, int height);
	// void drawTriangle(float* vertices, unsigned int* indices);
	 void setTexture(const char* filename, int* w, int* h, GLuint shaderID);
	 void Render();
};
#endif