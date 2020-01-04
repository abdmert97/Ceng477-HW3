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

GLFWwindow* window;


void OpenGL::Render()
{

	const char* windowName = "Ceng477";
	int screenHeight = 1000;
	int screenWidth = 1000;
	window = openWindow(windowName, screenWidth, screenHeight);
	// Create and compile our GLSL program from the shaders

	GLuint shader = LoadShaders("../VertexShader.vert", "../FragmentShader.frag");


	float vertices[] = {
		// positions          // normal           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
         -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
         -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
    glm::vec3 normal1 = calculateNormal(getPosition(vertices,0),getPosition(vertices,1),getPosition(vertices,2));
    setNormal(vertices,0,normal1);
    setNormal(vertices,1,normal1);
    setNormal(vertices,2,normal1);
    setNormal(vertices,3,normal1);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	const char* name = "../normal_earth_mini.jpg";
	setTexture(name, shader);
    initCamera(shader);
    glViewport(0,0, screenWidth, screenHeight);
   // glEnable(GL_DEPTH_TEST);
    //glUniform3f(glGetUniformLocation(shader, "lightcolor"), 0.3f,0.3f,0.3f);
    //glUniform3f(glGetUniformLocation(shader, "lightPos"), 0.0f,0.0f,0.0f);
    //Shader::setVec3("lightcolor",vec3(0.3f,0.3f,0.3f));
    //Ambient reflectence coefficient = ( 0 . 2 5 , 0. 2 5 , 0. 2 5 , 1 . 0 )
    //Ambient light color = ( 0 . 3 , 0 . 3 , 0 . 3 , 1 . 0 )
    //Specular reflectence coefficient = ( 1 . 0 , 1 . 0 , 1 . 0 , 1 . 0 )
    //Specular light color = ( 1 . 0 , 1 . 0 , 1 . 0 , 1 . 0 )
   // Specular exponent = 100
   // Diffuse reflectence coefficient = ( 1 . 0 , 1 . 0 , 1 . 0 , 1 . 0 )
   // Diffuse light color = ( 1 . 0 , 1 . 0 , 1 . 0 , 1 . 0 )
	do {

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// render container
		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	// Cleanup VBO
	glDeleteBuffers(1, &VAO);
	glDeleteProgram(shader);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}
GLFWwindow* OpenGL::openWindow(const char* windowName, int width, int height)
{
	GLFWwindow* window;
	// Initialise GLFW
	if (!glfwInit())
	{
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
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
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

void OpenGL::setTexture(const char* filename, GLuint shaderID)
{


	// texture 1
	// ---------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		imageWidth = width;
		imageHeight = height;

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glUseProgram(shaderID); // don't forget to activate/use the shader before setting uniforms!
 // either set it manually like so:
	glUniform1i(glGetUniformLocation(shaderID, "Tex"), 0);
}
glm::vec3  OpenGL::calculateNormal(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3)
{
    glm::vec3 N = glm::cross((v1 - v2) ,(v1 - v3)); //perform cross product of two lines on plane

    if(glm::length(N) > 0)
    {
        N = glm::normalize(N);  //normalize
    }
    return  N;
}

void OpenGL::initCamera(GLuint shaderID) {
    glm::vec3 gaze = glm::vec3(0,0,1);
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    cameraPosition = glm::vec3(imageWidth/2,imageWidth/10,-imageWidth/4);

    float projectionAngle = 45;
    float aspectRatio = 1;
    float near = 0.1;
    float far = 1000;
    glm::vec3 center = cameraPosition + gaze * near;

    glm::mat4 M_projection = glm::perspective(projectionAngle, aspectRatio, near, far);
    glm::mat4 M_view = glm::lookAt(cameraPosition, center, cameraUp);
    glm::mat4 M_model = glm::mat4(1.0f);

    glm::mat4 M_model_view_projection = M_projection * M_view * M_model;

    glm::mat4 M_normal = inverseTranspose(M_view);

    GLint loc_model_view = glGetUniformLocation(shaderID, "ModelViewMatrix");
    glUniformMatrix4fv(loc_model_view, 1, GL_FALSE, &M_view[0][0]);

    GLint loc_model_view_projection = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(loc_model_view_projection, 1, GL_FALSE, &M_model_view_projection[0][0]);

    GLint loc_normal = glGetUniformLocation(shaderID, "NormalMatrix");
    glUniformMatrix4fv(loc_normal, 1, GL_FALSE, &M_normal[0][0]);

    GLint lightPosition = glGetUniformLocation(shaderID, "lightPosition");
    glUniform3f(lightPosition, imageWidth/2,100,imageHeight/2);

    //GLint loc_camera_pos = glGetUniformLocation(shaderID, "cameraPosition");
   // glUniform3fv(loc_camera_pos, 1, &cameraPosition[0]);



    //uniform mat4 ModelViewMatrix;
    //uniform mat3 NormalMatrix;
    //uniform mat4 MVP;

}

glm::vec3 OpenGL::getPosition(float *vertices, int i) {
    return glm::vec3(vertices[8*i],vertices[8*i+1],vertices[8*i+2]);
}

void OpenGL::setNormal(float *vertices, int i, glm::vec3 normal)
{
    vertices[8*i+3] = normal.x;
    vertices[8*i+4] = normal.y;
    vertices[8*i+5] = normal.z;
 /*   cout<< vertices[8*i+3]<< " "<<
    vertices[8*i+4]<< " "<<
    vertices[8*i+5]<< " "<<endl;*/
}
