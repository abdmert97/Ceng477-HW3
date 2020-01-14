#include "SphereMap.h"
using namespace std;

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

void SphereMap::Render(const char *coloredTexturePath,const char *greyTexturePath) {
    // Open window
    GLFWwindow* window = openWindow(windowName, screenWidth, screenHeight);

    // Load shaders
    GLuint shaderID = LoadShaders("sphereShader.vert", "sphereShader.frag");

    initTexture(coloredTexturePath,shaderID);
    initTextureGrey(greyTexturePath,shaderID);
    setText(shaderID);
//---------------------------------------
    // Set Vertices
    for(int verticalStep = 0; verticalStep <= verticalSplitCount; ++verticalStep)
    {
        float stackAngle = verticalStep * PI / verticalSplitCount;
        float z = radius * cosf(stackAngle);              // r * sin(u)

        // add (horizontalSplitCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int horizontalStep = 0; horizontalStep <= horizontalSplitCount; ++horizontalStep)
        {
            float sectorAngle = horizontalStep * 2 * PI / horizontalSplitCount;           // starting from 0 to 2pi

           float x = radius * sinf(stackAngle) * cosf(sectorAngle);             // r * cos(u) * cos(v)
           float y = radius * sinf(stackAngle) * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            normals.push_back(x * (1 / radius));
            normals.push_back(y * (1 / radius));
            normals.push_back(z * (1 / radius));

            // vertex tex coord (s, t) range between [0, 1]
            texCoords.push_back((float)horizontalStep / horizontalSplitCount);
            texCoords.push_back((float)verticalStep / verticalSplitCount);
        }
    }

    for(int i = 0; i < verticalSplitCount; ++i)
    {
        int k1 = i * (horizontalSplitCount + 1);     // beginning of current stack
        int k2 = k1 + horizontalSplitCount + 1;      // beginning of next stack

        for(int j = 0; j < horizontalSplitCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (verticalSplitCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    std::vector<float>().swap(interleavedVertices);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i+1]);
        interleavedVertices.push_back(vertices[i+2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i+1]);
        interleavedVertices.push_back(normals[i+2]);

        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j+1]);
    }
//---------------------------------------



    // Configure Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(float), interleavedVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

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
        glViewport(0, 0, screenWidth, screenHeight);

        glClearStencil(0);
        glClearDepth(1.0f);
        glClearColor(0, 0, 0, 1);
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
        glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);

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

void SphereMap::handleKeyPress(GLFWwindow *window) {
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
        speed += 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
//        cout << "Key Press: H" << endl;
        speed -= 0.1;
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
        textureOffset -= 1.0 / horizontalSplitCount;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        cout << "Key Press: E" << endl;
        textureOffset += 1.0 / horizontalSplitCount;
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

//---------------------------------------
GLFWwindow *SphereMap::openWindow(const char *windowName, int width, int height) {
    if (!glfwInit()) {
        getchar();
        return 0;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    glfwSetWindowMonitor(window, NULL, 1, 31, screenWidth, screenHeight, NULL);

    if (window == NULL) {
        getchar();
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        getchar();
        glfwTerminate();
        return 0;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0, 0,0, 0);

    return window;
}
//---------------------------------------

void SphereMap::updateCamera(GLuint shaderID) {
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

void SphereMap::updateUniforms(GLuint shaderID){
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

void SphereMap::setText(GLuint shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureColor);
    glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, textureGrey);
    glUseProgram(shader); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shader, "TexColor"), 0);
    glUniform1i(glGetUniformLocation(shader, "TexGrey"), 1);
}
 void SphereMap::initTexture(const char *filename,GLuint shader)
{
    int width, height;
    glGenTextures(1, &textureColor);
    glBindTexture(GL_TEXTURE_2D, textureColor);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *raw_image = NULL;
    int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
    int color_space = JCS_RGB; /* or JCS_GRAYSCALE for grayscale images */

    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1];

    FILE *infile = fopen( filename, "rb" );
    unsigned long location = 0;
    int i = 0, j = 0;

    if ( !infile )
    {
        printf("Error opening jpeg file %s\n!", filename );
        return;
    }
    printf("Texture filename = %s\n",filename);

    /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error( &jerr );
    /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress( &cinfo );
    /* this makes the library read from infile */
    jpeg_stdio_src( &cinfo, infile );
    /* reading the image header which contains image information */
    jpeg_read_header( &cinfo, TRUE );
    /* Start decompression jpeg here */
    jpeg_start_decompress( &cinfo );

    /* allocate memory to hold the uncompressed image */
    raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );
    /* now actually read the jpeg into the raw buffer */
    row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
    /* read one scan line at a time */
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
            raw_image[location++] = row_pointer[0][i];
    }

    height = cinfo.image_height;
    width = cinfo.image_width;

    glGenTextures(1,&textureColor);
    glBindTexture(GL_TEXTURE_2D, textureColor);
    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, raw_image);
        // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    imageWidth = width;
    imageHeight = height;

    glGenerateMipmap(GL_TEXTURE_2D);

     glUseProgram(shader); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:

    glUniform1i(glGetUniformLocation(shader, "TexGrey"), 1);
    /* wrap up decompression, destroy objects, free pointers and close open files */
    jpeg_finish_decompress( &cinfo );
    jpeg_destroy_decompress( &cinfo );
    free( row_pointer[0] );
    free( raw_image );
    fclose( infile );

}

void SphereMap::initTextureGrey(const char *filename,GLuint shader)
{

     glGenTextures(1, &textureGrey);
    glBindTexture(GL_TEXTURE_2D, textureGrey);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height;

    unsigned char *raw_image = NULL;
    int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
    int color_space = JCS_RGB; /* or JCS_GRAYSCALE for grayscale images */

    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1];

    FILE *infile = fopen( filename, "rb" );
    unsigned long location = 0;
    int i = 0, j = 0;

    if ( !infile )
    {
        printf("Error opening jpeg file %s\n!", filename );
        return;
    }
    printf("Texture filename = %s\n",filename);

    /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error( &jerr );
    /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress( &cinfo );
    /* this makes the library read from infile */
    jpeg_stdio_src( &cinfo, infile );
    /* reading the image header which contains image information */
    jpeg_read_header( &cinfo, TRUE );
    /* Start decompression jpeg here */
    jpeg_start_decompress( &cinfo );

    /* allocate memory to hold the uncompressed image */
    raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );
    /* now actually read the jpeg into the raw buffer */
    row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
    /* read one scan line at a time */
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
            raw_image[location++] = row_pointer[0][i];
    }

    height = cinfo.image_height;
    width = cinfo.image_width;

    glGenTextures(1,&textureGrey);
    glBindTexture(GL_TEXTURE_2D, textureGrey);
    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, raw_image);
        // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    imageWidth = width;
    imageHeight = height;

    glGenerateMipmap(GL_TEXTURE_2D);

     glUseProgram(shader); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:

    glUniform1i(glGetUniformLocation(shader, "TexGrey"), 1);
    /* wrap up decompression, destroy objects, free pointers and close open files */
    jpeg_finish_decompress( &cinfo );
    jpeg_destroy_decompress( &cinfo );
    free( row_pointer[0] );
    free( raw_image );
    fclose( infile );

}

