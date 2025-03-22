#pragma once
#include <glm/glm.hpp>


class Shader {
private:
	void checkShaderCompilation(unsigned int& shader);
	void checkShaderProgramLinking(unsigned int& shaderProgram);

public:
	unsigned int ID;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use();
	void deleteShader();

	void setVec4f(const char* name, glm::vec4 vector);
	void setMat4f(const char* name, glm::mat4 matrix);
};