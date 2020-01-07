#ifndef OPENGL_H
#define OPENGL_H

#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


using namespace std;


class OpenGL {
private:
    glm::vec3 lightPos;
    bool pKeyPressed = false;
    // DISPLAY SETTINGS
    enum displayFormatOptions {
        windowed = 1, fullScreen = 0
    };
    const char *windowName = "Ceng477";
    int defaultScreenWidth = 1000;
    int defaultScreenHeight = 1000;
    int screenWidth = defaultScreenWidth;
    int screenHeight = defaultScreenHeight;
    int displayFormat = displayFormatOptions::windowed;
    // CAMERA SETTINGS
    float projectionAngle = 45;
    float aspectRatio = 1;
    float near = 0.1;
    float far = 1000;
    float pitch = 0;
    float yaw = 90;
    float speed = 0;
    glm::vec3 cameraStartPosition = glm::vec3(0, 100, 0);
    glm::vec3 cameraStartDirection = glm::vec3(0, 0, 1);
    glm::vec3 cameraUp = glm::vec3(0, 1, 0);
    glm::vec3 cameraPosition = cameraStartPosition;
    glm::vec3 cameraDirection = cameraStartDirection;
public:
    unsigned int texture;
    unsigned int VAO;
    unsigned int VBO, EBO;
    float imageHeight;
    float imageWidth;

    GLFWwindow *openWindow(const char *windowName, int width, int height);

    // void drawTriangle(float* vertices, unsigned int* indices);
    void setTexture(const char *filename, GLuint shaderID);

    void Render();

    static glm::vec3 calculateNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    void initCamera(GLuint shaderID);

    glm::vec3 getPosition(float *vertices, int i);

    void setNormal(float *vertices, int i, glm::vec3 normal);

    void handleKeyPress(GLFWwindow *window);

    void setCameraDirection();
};

#endif