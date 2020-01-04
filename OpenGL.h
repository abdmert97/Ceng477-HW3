#ifndef OPENGL_H
#define OPENGL_H
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


using namespace std;


class OpenGL
{
private:
    const char* windowName = "Ceng477";
    int screenHeight = 1000;
    int screenWidth = 1000;
public:
	 unsigned int texture;
	 unsigned int VAO;
	 unsigned int VBO, EBO;
	 unsigned int imageHeight;
	 unsigned int imageWidth;

	 glm::vec3 cameraPosition;
	 GLFWwindow* openWindow(const char* windowName, int width, int height);
	// void drawTriangle(float* vertices, unsigned int* indices);
	 void setTexture(const char* filename, GLuint shaderID);
	 void Render();
    static glm::vec3 calculateNormal(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3);
    void initCamera(GLuint shaderID);

    glm::vec3 getPosition(float *vertices, int i);

    void setNormal(float *vertices, int i, glm::vec3 normal);
};
#endif