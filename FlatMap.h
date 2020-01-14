#ifndef OPENGL_H
#define OPENGL_H

#include <vector>
#include <GL/glew.h>
#include <iostream>
#include "glm/glm/ext.hpp"
#include "Shader.hpp"
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
    float startPitch = 0;
    float startYaw = 90;
    float startSpeed = 0;
    float pitch = startPitch;
    float yaw = startYaw;
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

    void setTexture(const char *filenameColored, const char *filenameGray, GLuint shaderID);

    void Render();

    static glm::vec3 calculateNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    void updateCamera(GLuint shaderID);

    glm::vec3 getPosition(float *vertices, int i);

    void setNormal(float *vertices, int i, glm::vec3 normal);

    void handleKeyPress(GLFWwindow *window);

    void setCameraDirection();

    void printVec3(glm::vec3 vec);

    void updateUniforms(GLuint shaderID);

    void setText(GLuint shader);
    
   void initTexture(const char *filename,GLuint shader);
   void initTextureGrey(const char *filename,GLuint shader);
};

#endif
