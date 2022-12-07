#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
	public:
		// Stores the main three vectors used to find the cameras position
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		// Prevents camera snapping when first looking around
		bool firstClick = true;

		// stores width and height of the window
		int width;
		int height;
		
		// Adjust the speed of the camera and sensitivity
		float speed = 0.05f;
		float sensitivity = 100.0f;

		// Camera constructor to set up initial values
		Camera(int width, int height, glm::vec3 position);

		// Updates and exports the camera matrix to the Vertex shader
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window);
};
#endif
