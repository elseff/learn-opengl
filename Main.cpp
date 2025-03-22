#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include "Shader.h"
#include <stb_image/stb_image.h>
#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//struct UserData {
//	glm::mat4 viewMatrix;
//	glm::vec2 mousePos;
//};

int main()
{
	std::cout << std::boolalpha;

	// creating a GLFW window
	glfwInit();
	glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n";});

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	unsigned int width = 800;
	unsigned int height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "Rogue", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);

	//UserData userData;

	//glm::vec2 mousePos = glm::vec2(0.0f);
	//userData.mousePos = mousePos;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#if 0
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
#endif
	int imgWidth, imgHeight, nrChannels;
	unsigned char* data = stbi_load("Resources/Textures/container.jpg", &imgWidth, &imgHeight, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	Shader shader("Resources/Shaders/triangle.vert", "Resources/Shaders/triangle.frag");
	shader.use();

	// creating a vertext array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// creating a vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// loading data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// telling to shader how to read data from buffer
	glEnableVertexAttribArray(0);
	// 0 - location, 3 - 3 values (vec3), GL_FLOAT - float data type in vertices, GL_FALSE, quantity values in on vertex, and offset 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glPointSize(15);
	glLineWidth(5);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// fixed fps
	glfwSwapInterval(1);

	//GLint polygonMode;
	float time;
	float red;

	float angleDegrees = -90.0f;

	float scaleValue = 1.0f;

	//matrix = glm::scale(matrix, glm::vec3(0.5f,0.5f,0.5f));

	//Utils::printMatrix(matrix);

	//shader.setMat4f("transform", matrix);


	bool state = true;
	float angleVisibility = 45.0f;


	Camera camera(window,
				  glm::vec3(0.0f, 2.0f, 5.0f), // position
				  glm::vec3(0.0f), // target
		          glm::vec3(0.0f, 1.0f, 0.0f)); // up

	//userData.viewMatrix = camera.view;

	glm::mat4 view = camera.view;

	//glm::vec3 eye = glm::vec3(0.0f, angleVisibility / 50.0f + 1, 5.0f);
	//glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::mat4 view = glm::lookAt(eye, target, up);

	glm::mat4 projection = glm::perspective(glm::radians(angleVisibility), (float)width / (float)height, 0.1f, 100.0f); //WORK
	//glm::mat4 projection = glm::ortho((float)width / -2.0f, (float)width/2.0f, (float)height / -2.0f, (float)height/2.0f, -100.0f, 100.0f);
	//glm::mat4 projection = glm::ortho(-(float)width/2.0f, (float)width/2.0f, -(float)height/2.0f, (float)height/2.0f, -100.0f, 100.0f);
	//glm::mat4 view = glm::mat4(1.0f);
	shader.setMat4f("view", view);
	shader.setMat4f("projection", projection);

	//matrix = glm::scale(matrix, glm::vec3(width / 3.0f, height / 3.0f, 0.5f));
	//userData.viewMatrix = glm::scale(userData.viewMatrix, glm::vec3(angleVisibility / 50.0f));


#if 0
	std::cout << "view\n";
	Utils::printMatrix(view);
	std::cout << "projection\n";
	Utils::printMatrix(projection);
	std::cout << "view*projection\n";
	Utils::printMatrix(projection * view);
#endif
	glEnable(GL_DEPTH_TEST);
	float angle = 0.0f;
	float lastFrame = 0.0;
	while (!glfwWindowShouldClose(window))
	{

#if 0 
#if 1
		//clear console
		std::cout << "\033[2J\033[1;1H";
#endif
		float currentFrame = static_cast<float>(glfwGetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "delta:" << deltaTime << "\n";
		std::cout << "fps:" << static_cast<int>(1.0f / deltaTime) << "\n";
#endif
		/*if (scaleValue >= 1.0f) {
			state = false;
		}
		else if (scaleValue <= 0.5f) {
			state = true;
		}
		if (state) {
			scaleValue += 0.01f;
			angle += 1.8f / 50;
		}
		else {
			scaleValue -= 0.01f;
			angle -= 1.8f / 50;
		}*/
		//matrix = glm::mat4(1.0f);
	    //userData.modelMatrix = glm::rotate(userData.modelMatrix, glm::radians(1.8f), glm::vec3(0.0f, 0.5f, 0.0f));

		//userData.viewMatrix = glm::rotate(userData.viewMatrix, glm::radians(0.9f), glm::vec3(0.0f, 0.5f, 0.0f));
		shader.use();
		camera.move();
		camera.rotate();
		//userData.viewMatrix = camera.view;

		Utils::processInput(window);
		//glfwSetWindowUserPointer(window, &userData);

		//matrix = glm::scale(matrix, glm::vec3(scaleValue));

		//matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleValue));
		//matrix = glm::rotate(matrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		//matrix = glm::translate(glm::mat4(1.0f), glm::vec3(scaleValue-1, scaleValue-1, 0.0f)); 
		// !!!! matrix-vector product order very significant!
		shader.setMat4f("model", camera.view);
		//shader.setMat4f("view", view);

		glClearColor(0.7f, 0.5f, 0.8f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time = (float)glfwGetTime();
		red = (abs(sin(time)) / 1.5f) + 0.2f;

		shader.setVec4f("uniform_color", glm::vec4(red, 0.0f, 0.0f, 1.0f));

		//glBindVertexArray(VAO);

		// updating data in vbo
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 0));
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 6));

		glfwSwapBuffers(window);
		glfwPollEvents();
		shader.unuse();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture);
	shader.deleteShader();

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
