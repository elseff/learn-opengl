#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Consts.h"
#include <glm/glm.hpp>

namespace Utils {
	extern double value;
	extern bool state;
	extern Direction direction;
	extern const double speed;

	void processInput(GLFWwindow* window);
	std::string readFromFile(std::string path);
	// Функция для печати матрицы 4x4
	void printMatrix(const glm::mat4& matrix);
};