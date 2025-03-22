#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Camera {
	GLFWwindow* window;
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 view;
	float scale;
	float movementSpeed;

	static Camera* instance;

	Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 target, glm::vec3 up);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void rotate();
	void move();
};