#include "Camera.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Camera* Camera::instance = nullptr;

Camera::Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 target, glm::vec3 up) {
	this->position = position;
	this->target = target;
	this->up = up;

	this->view = glm::lookAt(position, target, up);
	this->movementSpeed = 0.05f;
	this->window = window;
	this->scale = 1.0f;
	instance = this;
	glfwSetScrollCallback(window, Camera::scroll_callback);
	glfwSetCursorPosCallback(window, Camera::mouse_callback);
}
bool state = false;
void Camera::rotate() {
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		
	}
}

bool first = true;

void Camera::move() {
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//Camera::target += glm::vec3(movementSpeed, 0.0f, 0.0f);
		//Camera::position += glm::vec3(movementSpeed, 0.0f, 0.0f);
		//Camera::mat_target = glm::translate(Camera::mat_target, glm::vec3(movementSpeed, 0.0f, 0.0f));
		//Camera::mat_position = glm::translate(Camera::mat_position, glm::vec3(movementSpeed, 0.0f, 0.0f));
		Camera::view = glm::translate(Camera::view, glm::vec3(-movementSpeed, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//Camera::target += glm::vec3(-movementSpeed, 0.0f, 0.0f);
		//Camera::position += glm::vec3(-movementSpeed, 0.0f, 0.0f);
		Camera::view = glm::translate(Camera::view, glm::vec3(movementSpeed, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//Camera::target -= (Camera::position - Camera::target) * movementSpeed;
		
//		Camera::target += glm::vec3(0.0f, 0.0f, -movementSpeed);
		//Camera::position += glm::vec3(0.0f, 0.0f, -movementSpeed);
		//Camera::position -= (Camera::position - Camera::target) * movementSpeed;
		Camera::view = glm::translate(Camera::view, (position - target)*movementSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//Camera::target += (Camera::position - Camera::target) * movementSpeed;

		//		Camera::target += glm::vec3(0.0f, 0.0f, -movementSpeed);
				//Camera::position += glm::vec3(0.0f, 0.0f, -movementSpeed);
		//Camera::position += (Camera::position - Camera::target) * movementSpeed;
		//Camera::view = glm::translate(Camera::view, (position + target)*movementSpeed);
		//Camera::position += (position * movementSpeed + target);
		Camera::view = glm::translate(Camera::view, (-position * movementSpeed + target));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//Camera::target += glm::vec3(0.0f, movementSpeed, 0.0f);
		//Camera::position += glm::vec3(0.0f, movementSpeed, 0.0f);
		//Camera::position += (position * movementSpeed + target);
		Camera::view = glm::translate(Camera::view, glm::vec3(0.0f, -movementSpeed, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		//Camera::target += glm::vec3(0.0f, -movementSpeed, 0.0f);
		//Camera::position += glm::vec3(0.0f, -movementSpeed, 0.0f);
		//Camera::position += (position * movementSpeed + target);
		//Camera::view = glm::translate(Camera::view, (-position * movementSpeed + target));
		Camera::view = glm::translate(Camera::view, glm::vec3(0.0f, movementSpeed, 0.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (!state) {
			state = true;
			std::cout << "current scale:" << instance->scale << "\n";
			std::cout << "reset to " << 1.0f / Camera::scale << "\n";
			Camera::view = glm::scale(instance->view, glm::vec3(1.0f / Camera::scale));
			Camera::scale = 1.0f;
		}
		//Camera::target += glm::vec3(0.0f, -movementSpeed, 0.0f);
		//Camera::position += glm::vec3(0.0f, -movementSpeed, 0.0f);
		//Camera::position += (position * movementSpeed + target);
		//Camera::view = glm::translate(Camera::view, (-position * movementSpeed + target));	
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		state = false;
	}
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (instance) {
		float temp = 1.0f + static_cast<float>(yoffset) / 10.0f;
		instance->scale += static_cast<float>(yoffset) / 10.0f;;
		std::cout << "scale:" << instance->scale << "\n";
		instance->view = glm::scale(instance->view, glm::vec3(instance->scale));
	}
}


void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	
}