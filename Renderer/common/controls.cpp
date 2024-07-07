#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}

glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}


//position
glm::vec3 position = glm::vec3(0, 0, 5);

//horizontal angle : toward -Z
float horizontalAngle = 3.14f;
//vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
//initial FOV
float initialFoV = 60.0f;

float speed = 20.0f;
float mouseSpeed = 0.2f;


void computeMatricesFromInputs() {

	//glfwGetTime is called only once, when this function is first called
	static double lastTime = glfwGetTime();

	//compute the time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);


	//get mouse pos
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	//reset mouse pos for next frame
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window,  width / 2, height / 2);

	//compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(width / 2 - xpos);
	verticalAngle += mouseSpeed/1.5 * deltaTime * float(height / 2 - ypos);


	//direction : spherical coordinates to cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	//right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	//to find the up vector from the direction (front) and right vector we just need to take the cross product

	glm::vec3 up = glm::cross(right, direction);


	//key detection -----------------
	//forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	//backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	//right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	//left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)  {
		position -= right * deltaTime * speed;
	}
	//up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += up * deltaTime * speed;
	}

	//projection matrix : 45 deg FOV, 4:3 ratio, 0.1-100 unit display range
	ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 300.0f);

	//camera matrix
	ViewMatrix = glm::lookAt(
		position,
		position+direction,
		up
	);

	lastTime = currentTime;
}
