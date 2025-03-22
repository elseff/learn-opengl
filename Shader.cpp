#include "Shader.h"
#include "Utils.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexShaderSource = Utils::readFromFile(vertexShaderPath);
	std::string fragmentShaderSource = Utils::readFromFile(fragmentShaderPath);

	const char* vShaderSource = vertexShaderSource.c_str();
	const char* fShaderSource = fragmentShaderSource.c_str();
	/*
		██    ██ ███████ ██████  ████████ ███████ ██   ██
		██    ██ ██      ██   ██    ██    ██       ██ ██
		██    ██ █████   ██████     ██    █████     ███
		 ██  ██  ██      ██   ██    ██    ██       ██ ██
		  ████   ███████ ██   ██    ██    ███████ ██   ██

		███████ ██   ██  █████  ██████  ███████ ██████
		██      ██   ██ ██   ██ ██   ██ ██      ██   ██
		███████ ███████ ███████ ██   ██ █████   ██████
			 ██ ██   ██ ██   ██ ██   ██ ██      ██   ██
		███████ ██   ██ ██   ██ ██████  ███████ ██   ██
	*/
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader);

	/*
		███████ ██████   █████   ██████  ███    ███ ███████ ███    ██ ████████
		██      ██   ██ ██   ██ ██       ████  ████ ██      ████   ██    ██
		█████   ██████  ███████ ██   ███ ██ ████ ██ █████   ██ ██  ██    ██
		██      ██   ██ ██   ██ ██    ██ ██  ██  ██ ██      ██  ██ ██    ██
		██      ██   ██ ██   ██  ██████  ██      ██ ███████ ██   ████    ██

		███████ ██   ██  █████  ██████  ███████ ██████
		██      ██   ██ ██   ██ ██   ██ ██      ██   ██
		███████ ███████ ███████ ██   ██ █████   ██████
		     ██ ██   ██ ██   ██ ██   ██ ██      ██   ██
		███████ ██   ██ ██   ██ ██████  ███████ ██   ██
		
	*/
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader);

	// creating shader program
	ID = glCreateProgram();

	// attaching and linking shaders into shader program / and check shader linking
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkShaderProgramLinking(ID);

	// deleteing shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::deleteShader()
{
	glDeleteProgram(ID);
}

void Shader::setVec4f(const char* name, glm::vec4 vector)
{
	// fix that
	// you should glGetUniformLocation once in constructor, save location and pass it in glUniform call
	glUniform4f(glGetUniformLocation(ID, name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setMat4f(const char* name, glm::mat4 matrix) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkShaderCompilation(unsigned int& shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
			<< "\n  -- --------------------------------------------------- -- \n";
	}
}

void Shader::checkShaderProgramLinking(unsigned int& shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
			<< "\n  -- --------------------------------------------------- -- \n";
	}
}