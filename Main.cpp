#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW which version we are using; 3.3 as of 12/4/22
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the "core" profile, meaning we don't care about legacy functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates a GLFW window that is 800x800 pixels, and name it accordingly.
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL project", NULL, NULL);

	// Make the window we just created the current context
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();

	// Specify the OpenGL viewport
	glViewport(0, 0, width, height);

	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /     COLORS               /  TEXCOORDS   
		-0.5f,  0.0f,  0.5f,     0.83f,  0.70f,  0.44f,    0.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,     0.83f,  0.70f,  0.44f,    5.0f, 0.0f,
		 0.5f,  0.0f, -0.5f,     0.83f,  0.70f,  0.44f,    0.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,     0.83f,  0.70f,  0.44f,    5.0f, 0.0f,
		 0.0f,  0.8f,  0.0f,     0.92f,  0.86f,  0.76f,    2.5f, 5.0f
	};

	GLuint indices[] =
	{
		0, 1, 2, 
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	// Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	// Generates Vertex Array Object with binding
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and Element Buffer Object and links them to their vertices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// unbind all to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Texture
	Texture dun("dun.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	dun.texUnit(shaderProgram, "tex0", 0);

	// Enables depth testing for better 3D rendering
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while(!glfwWindowShouldClose(window)) 
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we are using
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Bind texture so it renders
		dun.Bind();
		// Bind the VAO so OpenGL knows we are using it
		VAO1.Bind();
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// let GLFW do what it needs to, all managed by itself
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	dun.Delete();
	shaderProgram.Delete();

	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}