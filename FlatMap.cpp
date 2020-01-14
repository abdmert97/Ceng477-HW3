// Include GLM


#include "FlatMap.h"


#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


using namespace std;

GLFWwindow *window;

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    vertex() {}

    vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texture) : position(position),
                                                                                           normal(normal),
                                                                                           texture(texture) {}
};

struct triangle {
    int vertex1;
    int vertex2;
    int vertex3;

    triangle() {}

    triangle(const int &vertex1, const int &vertex2, const int &vertex3) : vertex1(vertex1), vertex2(vertex2),
                                                                           vertex3(vertex3) {}
};

void FlatMap::Render() {
    // Open window
    window = openWindow(windowName, screenWidth, screenHeight);

    // Load shaders
    GLuint shaderID = LoadShaders("../flatShader.vert", "../flatShader.frag");

    // Set Texture
    const char *coloredTexturePath = "../normal_earth_mini.jpg";
    const char *greyTexturePath = "../height_gray_mini.jpg";
    setTexture(coloredTexturePath, greyTexturePath, shaderID);

    // Initialize data structures
    vector<vertex> vertices(imageWidth * imageHeight);      // Four vertices for every pixel
    vector<triangle> indices(imageWidth * imageHeight * 2); // Two triangles for every pixel

    // Set Vertices
    for (int i = 0; i < imageHeight; i++) {
        for (int j = 0; j < imageWidth; j++) {
            vertices[i * imageWidth + j].position = glm::vec3(j, 0, i);
            vertices[i * imageWidth + j].normal = glm::vec3(0, -1, 0);
            vertices[i * imageWidth + j].texture = glm::vec2(1 - ((float) j) / imageWidth,
                                                             1 - ((float) i) / imageHeight);
        }
    }

    // Set Indices
    int currentIndex = 0;
    for (int i = 0; i < imageHeight - 1; i++) {
        for (int j = 0; j < imageWidth - 1; j++) {
            indices[currentIndex].vertex1 = i * imageWidth + j;
            indices[currentIndex].vertex2 = i * imageWidth + j + 1;
            indices[currentIndex].vertex3 = i * imageWidth + imageWidth + j;
            currentIndex++;

            indices[currentIndex].vertex1 = i * imageWidth + j + 1;
            indices[currentIndex].vertex2 = i * imageWidth + imageWidth + j + 1;
            indices[currentIndex].vertex3 = i * imageWidth + imageWidth + j;
            currentIndex++;
        }
    }


    // Configure Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(triangle), indices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    do {
        // Refresh viewport
        glViewport(0, 0, screenWidth, screenHeight);
        glClearStencil(0);
        glClearDepth(1.0f);
        glClearColor(0.2, 0.3, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Update camera at every frame
        updateCamera(shaderID);

        // Update uniform variables at every frame
        updateUniforms(shaderID);

        // Handle key presses
        handleKeyPress(window);

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColor);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureGrey);

        // Use shaderID program
        glUseProgram(shaderID);

        glBindVertexArray(VAO);

        // Draw
        glDrawElements(GL_TRIANGLES, 3 * 2 * (imageHeight) * (imageWidth), GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (!glfwWindowShouldClose(window));

    // Delete buffers
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderID);

    // Close window
    glfwTerminate();
}

void FlatMap::handleKeyPress(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        cout << "Key Press: ESC" << endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        cout << "Key Press: W" << endl;
        glm::vec3 cameraLeft = glm::cross(cameraDirection, cameraUp);
        cameraUp = glm::rotate(cameraUp, 0.01f, cameraLeft);
        cameraDirection = glm::rotate(cameraDirection, 0.01f, cameraLeft);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        cout << "Key Press: S" << endl;
        glm::vec3 cameraLeft = glm::cross(cameraDirection, cameraUp);
        cameraUp = glm::rotate(cameraUp, -0.01f, cameraLeft);
        cameraDirection = glm::rotate(cameraDirection, -0.01f, cameraLeft);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        cout << "Key Press: D" << endl;
        cameraDirection = glm::rotate(cameraDirection, -0.01f, cameraUp);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        cout << "Key Press: A" << endl;
        cameraDirection = glm::rotate(cameraDirection, 0.01f, cameraUp);
    }


    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
//        cout << "Key Press: Y" << endl;
        speed += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
//        cout << "Key Press: H" << endl;
        speed -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
//        cout << "Key Press: X" << endl;
        speed = 0;
    }


    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
//        cout << "Key Press: ->" << endl;
        lightPos.x -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
//        cout << "Key Press: <-" << endl;
        lightPos.x += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//        cout << "Key Press: ^" << endl;
        lightPos.z += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//        cout << "Key Press: v" << endl;
        lightPos.z -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
//        cout << "Key Press: T" << endl;
        lightPos.y += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
//        cout << "Key Press: G" << endl;
        lightPos.y -= 5;
    }


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
//        cout << "Key Press: R" << endl;
        heightFactor += 0.5;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
//        cout << "Key Press: F" << endl;
        heightFactor -= 0.5;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        cout << "Key Press: Q" << endl;
        textureOffset -= 1 / imageWidth;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        cout << "Key Press: E" << endl;
        textureOffset += 1 / imageWidth;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
//        cout << "Key Press: I" << endl;
        cameraPosition = cameraStartPosition;
        cameraDirection = cameraStartDirection;
        cameraUp = cameraStartUp;
        pitch = startPitch;
        yaw = startYaw;
        speed = startSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
//        cout << "Key Press: P" << endl;
        pKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && pKeyPressed) {
//        cout << "Key Release: P" << endl;
        if (displayFormat == displayFormatOptions::windowed) {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            screenWidth = mode->width;
            screenHeight = mode->height;
            displayFormat = displayFormatOptions::fullScreen;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, screenWidth, screenHeight, mode->refreshRate);
        } else if (displayFormat == displayFormatOptions::fullScreen) {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            screenWidth = defaultScreenWidth;
            screenHeight = defaultScreenHeight;
            displayFormat = displayFormatOptions::windowed;
            glfwSetWindowMonitor(window, NULL, 1, 31, screenWidth, screenHeight, mode->refreshRate);
        }
        pKeyPressed = false;
    }
}


GLFWwindow *FlatMap::openWindow(const char *windowName, int width, int height) {

    GLFWwindow *window;
    if (!glfwInit()) {
        getchar();
        return 0;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    glfwSetWindowMonitor(window, NULL, 1, 31, screenWidth, screenHeight, NULL);

    if (window == NULL) {
        getchar();
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
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

void FlatMap::setTexture(const char *filenameColored, const char *filenameGray, GLuint shaderID) {
    glGenTextures(1, &textureColor);
    glBindTexture(GL_TEXTURE_2D, textureColor);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    int stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    cout << filenameColored << " " << filenameGray << endl;
    unsigned char *dataColored = stbi_load(filenameColored, &width, &height, &nrChannels, 0);

    if (dataColored) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataColored);
        glGenerateMipmap(GL_TEXTURE_2D);

        imageWidth = width;
        imageHeight = height;
        cout << "Texture width: " << width << " height: " << height << endl;
        // Init light position right after obtaining image width/height
        lightPos = glm::vec3(imageWidth / 2.0f, 100, imageHeight / 2.0f);
        cameraPosition = glm::vec3(imageWidth / 2.0f, imageWidth / 10.0f, -imageWidth / 4.0f);

        cameraStartPosition = cameraPosition;

    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(dataColored);
    glGenTextures(1, &textureGrey);
    glBindTexture(GL_TEXTURE_2D, textureGrey);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char *dataGray = stbi_load(filenameGray, &width, &height, &nrChannels, 0);
    if (dataGray) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataGray);
        glGenerateMipmap(GL_TEXTURE_2D);


    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    glUseProgram(shaderID); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shaderID, "TexColor"), 0);
    glUniform1i(glGetUniformLocation(shaderID, "TexGrey"), 1);

    stbi_image_free(dataGray);

}



void FlatMap::updateCamera(GLuint shaderID) {
    cameraPosition += speed * cameraDirection;
    
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(projectionAngle), aspectRatio, near, far);
    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);

    glm::mat4 MVPMatrix = projectionMatrix * viewMatrix;

    glm::mat4 MVPMatrixNormal = inverseTranspose(viewMatrix);

    GLint projectionMatrixId = glGetUniformLocation(shaderID, "ProjectionMatrix");
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);

    GLint viewMatrixId = glGetUniformLocation(shaderID, "ViewMatrix");
    glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);

    GLint MVPMatrixId = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MVPMatrixId, 1, GL_FALSE, &MVPMatrix[0][0]);

    GLint MVPMatrixNormalId = glGetUniformLocation(shaderID, "NormalMatrix");
    glUniformMatrix4fv(MVPMatrixNormalId, 1, GL_FALSE, &MVPMatrixNormal[0][0]);
}

void FlatMap::updateUniforms(GLuint shaderID){
    GLint cameraPositionId = glGetUniformLocation(shaderID, "cameraPosition");
    glUniform3fv(cameraPositionId, 1, &cameraPosition[0]);

    GLint lightPositionId = glGetUniformLocation(shaderID, "lightPosition");
    glUniform3fv(lightPositionId, 1, &lightPos[0]);

    GLint heightFactorId = glGetUniformLocation(shaderID, "heightFactor");
    glUniform1f(heightFactorId, this->heightFactor);


    GLint imageWidthId = glGetUniformLocation(shaderID, "imageWidth");
    glUniform1f(imageWidthId, this->imageWidth);


    GLint imageHeightId = glGetUniformLocation(shaderID, "imageHeight");
    glUniform1f(imageHeightId, this->imageHeight);

    GLint textureOffsetId = glGetUniformLocation(shaderID, "textureOffset");
    glUniform1f(textureOffsetId, this->textureOffset);
}
