// Include GLM

#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <glm/ext.hpp>
#include "OpenGL.h"
#include "Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


using namespace std;

GLFWwindow *window;
struct vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;


    vertex(glm::vec3 pos, glm::vec3 norm,glm::vec2 tex)
    {
        position = pos;
        normal = norm;
        texture = tex;
    }
};

void OpenGL::Render() {
    // Open window
    window = openWindow(windowName, screenWidth, screenHeight);

    // Create and compile our GLSL program from the shaders
    GLuint shader = LoadShaders("../shader.vert", "../shader.frag");

    // Set Texture
    const char *name = "../normal_earth_mini.jpg";
    setTexture(name, shader);

    // Set Vertices
    float vertices2[] = {
            // positions         // normal           // texture coords
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    float right = imageWidth / 2;
    float top = imageHeight / 2;
    /*float vertices[] = {
            right, 0.0f, top, .0f, 0.0f, 0.0f, 0.0f, 1.0f, // top right
            right, 0.0f, -top, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom right
            -right, 0.0f, top, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top left

            right, 0.0f, -top, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom right
            -right, 0.0f, -top, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
            -right, 0.0f, top, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f  // top left
    };*/
    vector<vertex> vertices;
    vector<unsigned int> indices;
    for (int i = 0; i <= imageHeight; i++)
    {
        for (int j = 0; j <= imageWidth; j++)
        {
            //start from left bottom  = 0,0,0
            glm::vec3 position = glm::vec3(j,0,i);
            glm::vec3 normal = glm::vec3(0,0,0);
            glm::vec2 texture = glm::vec2((float)j/imageWidth,(float)i/imageHeight);

            vertices.push_back(vertex(position,normal,texture));

        }
    }

   /* unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3
          // second triangle
    };
*/

   for(int i = 0 ; i< (imageWidth-1)*(imageHeight-1); i++)
   {
       indices.push_back(i);
       indices.push_back(i+1);
       indices.push_back(i+imageWidth);

       indices.push_back(i+1);
       indices.push_back(i+1+imageWidth);
       indices.push_back(i+imageWidth);
   }

    // Normal Calculation
    /*glm::vec3 normal1 = calculateNormal(getPosition(vertices, 0), getPosition(vertices, 1), getPosition(vertices, 2));
    setNormal(vertices, 0, normal1);
    setNormal(vertices, 1, normal1);
    setNormal(vertices, 2, normal1);
    setNormal(vertices, 3, normal1);
    setNormal(vertices, 4, normal1);
    setNormal(vertices, 5, normal1);*/
    for(int i = 0 ; i < vertices.size() ;i++)
    {
        glm::vec3 normal = glm::vec3 (0,0,-1);
    }


    // Configure Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    // Configure Camera
    initCamera(shader);

    glEnable(GL_DEPTH_TEST);
    do {
        glViewport(0, 0, screenWidth, screenHeight);

        glClearStencil(0);
        glClearDepth(1.0f);
        glClearColor(0.2, 0.3, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        initCamera(shader);


        handleKeyPress(window);


        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        // render container
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3 * 2 * (imageHeight ) * (imageWidth ), GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (!glfwWindowShouldClose(window));

    // Cleanup VBO
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

void OpenGL::handleKeyPress(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        cout << "Key Press: ESC" << endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cout << "Key Press: W" << endl;
        pitch += 0.5;
        setCameraDirection();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cout << "Key Press: S" << endl;
        pitch -= 0.5;
        setCameraDirection();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cout << "Key Press: D" << endl;
        yaw += 0.5;
        setCameraDirection();
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cout << "Key Press: A" << endl;
        yaw -= 0.5;
        setCameraDirection();
    }


    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        cout << "Key Press: Y" << endl;
        speed += 0.025;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        cout << "Key Press: H" << endl;
        speed -= 0.025;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        cout << "Key Press: X" << endl;
        speed = 0;
    }


    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cout << "Key Press: ->" << endl;
        lightPos.x += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cout << "Key Press: <-" << endl;
        lightPos.x -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cout << "Key Press: ^" << endl;
        lightPos.z += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cout << "Key Press: v" << endl;
        lightPos.z -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        cout << "Key Press: T" << endl;
        lightPos.y += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        cout << "Key Press: G" << endl;
        lightPos.y -= 5;
    }


    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        cout << "Key Press: I" << endl;
        cameraPosition = cameraStartPosition;
        cameraDirection = cameraStartDirection;
        speed = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        cout << "Key Press: P" << endl;
        pKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && pKeyPressed) {
        cout << "Key Release: P" << endl;
        if(displayFormat == displayFormatOptions::windowed)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            screenWidth = mode->width;
            screenHeight = mode->height;
            displayFormat = displayFormatOptions::fullScreen;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, screenWidth, screenHeight, mode->refreshRate);
        }
        else if(displayFormat == displayFormatOptions::fullScreen){
            screenWidth = defaultScreenWidth;
            screenHeight = defaultScreenHeight;
            displayFormat = displayFormatOptions::windowed;
            glfwSetWindowMonitor(window, NULL, 1, 31, screenWidth, screenHeight, NULL);
        }
        pKeyPressed = false;
    }
}

// TODO: doruktan alindi yeniden yazilmali!!!
void OpenGL::setCameraDirection() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->cameraDirection = glm::normalize(front);
}


GLFWwindow *OpenGL::openWindow(const char *windowName, int width, int height) {
    GLFWwindow *window;
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return 0;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    glfwSetWindowMonitor(window, NULL, 1, 31, screenWidth, screenHeight, NULL);
    if (window == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return 0;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    return window;
}

void OpenGL::setTexture(const char *filename, GLuint shaderID) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        imageWidth = width;
        imageHeight = height;
        cout << "Texture width: " << width << " height: " << height << endl;
        // Init light position right after obtaining image width/height
        lightPos = glm::vec3(imageWidth / 2.0f, 100, imageHeight / 2.0f);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glUseProgram(shaderID); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shaderID, "Tex"), 0);
}


glm::vec3 OpenGL::calculateNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    glm::vec3 N = glm::cross((v1 - v2), (v1 - v3)); //perform cross product of two lines on plane

    if (glm::length(N) > 0) {
        N = glm::normalize(N);  //normalize
    }
    return N;
}


void OpenGL::initCamera(GLuint shaderID) {
    cameraPosition += speed * cameraDirection;
    glm::mat4 M_projection = glm::perspective(glm::radians(projectionAngle), aspectRatio, near, far);
    glm::mat4 M_view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
    glm::mat4 M_model = glm::mat4(1.0f);

    glm::mat4 M_model_view_projection = M_projection * M_view;

    glm::mat4 M_normal = inverseTranspose(M_view);

    GLint loc_projection = glGetUniformLocation(shaderID, "ProjectionMatrix");
    glUniformMatrix4fv(loc_projection, 1, GL_FALSE, &M_projection[0][0]);

    GLint loc_model_view = glGetUniformLocation(shaderID, "ViewMatrix");
    glUniformMatrix4fv(loc_model_view, 1, GL_FALSE, &M_view[0][0]);

    GLint loc_model_view_projection = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(loc_model_view_projection, 1, GL_FALSE, &M_model_view_projection[0][0]);

    GLint loc_normal = glGetUniformLocation(shaderID, "NormalMatrix");
    glUniformMatrix4fv(loc_normal, 1, GL_FALSE, &M_normal[0][0]);

    GLint loc_camera_pos = glGetUniformLocation(shaderID, "cameraPosition");
    glUniform3fv(loc_camera_pos, 1, &cameraPosition[0]);

    GLint camPosition = glGetUniformLocation(shaderID, "cameraPosition");
    glUniform3fv(camPosition, 1, &cameraPosition[0]);

    GLint lightPosition = glGetUniformLocation(shaderID, "lightPosition");
    glUniform3fv(lightPosition, 1, &lightPos[0]);

}
void OpenGL::printVec3( glm::vec3 vec)
{
    cout << "Vector : "<< vec.x  << " " << " " << vec.y<<" "<< vec.z<< endl;
}

glm::vec3 OpenGL::getPosition(float *vertices, int i) {
    return glm::vec3(vertices[8 * i], vertices[8 * i + 1], vertices[8 * i + 2]);
}


void OpenGL::setNormal(float *vertices, int i, glm::vec3 normal) {
    vertices[8 * i + 3] = normal.x;
    vertices[8 * i + 4] = normal.y;
    vertices[8 * i + 5] = normal.z;
    /*   cout<< vertices[8*i+3]<< " "<<
       vertices[8*i+4]<< " "<<
       vertices[8*i+5]<< " "<<endl;*/
}
