#ifndef OPENGL_H
#define OPENGL_H

#include <vector>
#include <GL/glew.h>
#include <iostream>
#include "glm/glm/ext.hpp"
#include "Shader.h"
#include <vector>
#include "glm/glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <jpeglib.h>
#include <GL/glew.h>


using namespace std;


class FlatMap {
private:
    float heightFactor = 10;
    float textureOffset = 0;
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
    float far = 10000;
    float startSpeed = 0;
    float speed = startSpeed;
    glm::vec3 cameraStartPosition = glm::vec3(0, 100, 0);
    glm::vec3 cameraStartDirection = glm::vec3(0, 0, 1);
    glm::vec3 cameraStartUp = glm::vec3(0, 1, 0);
    glm::vec3 cameraUp = cameraStartUp;
    glm::vec3 cameraPosition = cameraStartPosition;
    glm::vec3 cameraDirection = cameraStartDirection;
public:
    unsigned int textureColor;
    unsigned int textureGrey;
    unsigned int VAO;
    unsigned int VBO, EBO;
    float imageHeight;
    float imageWidth;

    GLFWwindow *openWindow(const char *windowName, int width, int height);

    void Render(const char *coloredTexturePath,const char *greyTexturePath);

    void updateCamera(GLuint shaderID);

    void handleKeyPress(GLFWwindow *window);

    void updateUniforms(GLuint shaderID);
    
   void initColoredTexture(const char *filename, GLuint shader);

   void initGreyTexture(const char *filename, GLuint shader);
};

#endif
