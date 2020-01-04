#ifndef OPENGL_H
#define OPENGL_H
#include "OpenGLHelper.h"
#include <vector>
using  namespace  glm;
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