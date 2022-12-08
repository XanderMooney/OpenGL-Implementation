#include"Model.h"

const unsigned int width = 1080;
const unsigned int height = 1080;


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

	// Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Enables depth testing for better 3D rendering
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/map/scene.gtlf");

	// Main while loop
	while(!glfwWindowShouldClose(window)) 
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		glfwSwapBuffers(window);
		// let GLFW do what it needs to, all managed by itself
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();

	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}