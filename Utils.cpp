#include "Utils.h"
#include "Consts.h"


#include <iostream>
#include <string>
#include <fstream>  // для std::ifstream
#include <sstream>  // для std::stringstream
#include <unordered_map>
#include <iomanip> // Для std::setw и std::setprecision
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Utils {
	extern double value = 0.0;
	extern bool state = true;
	Direction direction = Direction::UP;
	extern const double speed = 0.02;
	bool pressed = false;
	int  inverse = 1;

	std::unordered_map<int, bool> pressedKeys;

	void processInput(GLFWwindow* window, glm::mat4& matrix)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			if (pressedKeys.find(GLFW_KEY_K) == pressedKeys.end()) {
				pressedKeys[GLFW_KEY_K] = GLFW_RELEASE;
			}
			if (!pressedKeys[GLFW_KEY_K]) {
				pressedKeys[GLFW_KEY_K] = GLFW_PRESS;

				GLint polygonMode;
				glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
				if (polygonMode == GL_FILL) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					return;
				}
				else if (polygonMode == GL_LINE) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					return;
				}
			}
		}
		else {
			pressedKeys[GLFW_KEY_K] = GLFW_RELEASE;
		}
#if 0
		//clear console
		std::cout << "\033[2J\033[1;1H";
		std::cout << "pressed keys\n";
		for (const auto& pair : pressedKeys) {
			if (pair.second)
			{
				std::cout << glfwGetKeyName(pair.first, 0) << "=press\n";
			}
		}
#endif
#if 0
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
			value += speed;
			switch (direction) {
			case Direction::UP: {
				if (value >= 1.0f) {
					direction = Direction::RIGHT;
					//std::cout << "Turning right\n";
					value = 0.0f;
				}
				//change z position
				matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, speed));
				break;
			}
			case Direction::DOWN: {
				if (value >= 1.0f) {
					direction = Direction::LEFT;
					//std::cout << "Turning left\n";
					value = 0.0f;
				}
				//change z position
				matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, -speed));
				break;
			}
			case Direction::LEFT: {
				if (value >= 1.0f) {
					direction = Direction::UP;
					//std::cout << "Turning up\n";
					value = 0.0f;
				}
				//change x position
				matrix = glm::translate(matrix, glm::vec3(-speed, 0.0f, 0.0f));
				break;
			}
			case Direction::RIGHT: {
				if (value >= 1.0f) {
					direction = Direction::DOWN;
					//std::cout << "Turning down\n";
					value = 0.0f;
				}
				//change x position
				matrix = glm::translate(matrix, glm::vec3(speed, 0.0f, 0.0f));
				break;
			}
			}
		}
		#endif
	}

	std::string readFromFile(std::string path)
	{

		std::ifstream in(path);
		std::stringstream buffer;
		buffer << in.rdbuf();

		return (std::string)buffer.str();
	}

	void printMatrix(const glm::mat4& matrix) {
		// Настройка форматирования (2 знака после запятой)
		std::cout << std::fixed << std::setprecision(4);

		// Верхняя граница таблицы
		std::cout << "+---------+---------+---------+---------+" << std::endl;

		for (int i = 0; i < 4; ++i) { // Проходим по строкам
			std::cout << "| "; // Левая граница строки
			for (int j = 0; j < 4; ++j) { // Проходим по столбцам
				// Печатаем элемент матрицы с выравниванием
				std::cout << std::setw(7) << matrix[j][i] << " | ";
			}
			std::cout << std::endl; // Переход на новую строку

			// Горизонтальная граница между строками (кроме последней)
			if (i < 3) {
				std::cout << "+---------+---------+---------+---------+" << std::endl;
			}
		}

		// Нижняя граница таблицы
		std::cout << "+---------+---------+---------+---------+" << std::endl;
	}
}