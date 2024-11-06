#include "../Include/glad/glad.h"
#include "glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include <random>
#include <functional>

#define Z_DEFAULT 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
bool boundsCheck(float pos);
float randomFloat(float min, float max);
float randomPoint();

void on_up(GLFWwindow* window, std::function<void()> callback);
void on_down(GLFWwindow* window, std::function<void()> callback);
void on_left(GLFWwindow* window, std::function<void()> callback);
void on_right(GLFWwindow* window, std::function<void()> callback);

float x_offset = 0.0f;
float y_offset = 0.0f;

//old code

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0); "
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


struct Triangle;
struct Vert;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(900, 600, "Hey look it's a cool window", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "something did a fucky wucky" << std::endl;
		return -1;
	}

	glViewport(0, 0, 900, 600);


	

	//initialize shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//compile shaders
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,

		-1, -1, .0f,
		.1f, -.1f, .0f,
		0.0f, 0.1f, 0.0f
	};

	//vertex buffer
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float speed = 0.01f;

	glm::vec2 direction = glm::normalize(glm::vec2(randomPoint(), randomPoint()));
	float posX = randomPoint();
	float posY = randomPoint();

	while (!glfwWindowShouldClose(window))
	{
		//process input
		process_input(window);

		//render stuff here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		/*
		posX += direction.x * speed;
		posY += direction.y * speed;

		if (boundsCheck(posX))
		{
			direction.x *= -1;
			posX += direction.x * speed;
		}

		if (boundsCheck(posY))
		{
			direction.y *= -1;
			posY += direction.y * speed;
		}
		*/

		glUseProgram(shaderProgram);


		glm::mat4 transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3(x_offset, y_offset, 0.0f));
		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLocation = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//callbacks/events/buffer management
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();


	/*Triangle* t = new Triangle(
		{
			0.0f,
			0.1f,
			0.0f,
		},
		{
			0.0f,
			0.1f,
			0.0f,
		},
			{
			0.0f,
			0.1f,
			0.0f,
		});

	float* array = t->toArray();*/

	//return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	on_up(window, []() {
		if (!boundsCheck(y_offset)) {
			y_offset += .01f;
		}
		else {
			y_offset = .99f;
		}
		});

	on_down(window, []() {
		if (!boundsCheck(y_offset)) {
			y_offset -= .01f;
		}
		else {
			y_offset = -.99f;
		}
		});

	on_left(window, []() {
		if (!boundsCheck(x_offset)) {
			x_offset -= .01f;
		}
		else {
			x_offset = -0.99f;
		}
		});

	on_right(window, []() {
		if (!boundsCheck(x_offset)) {
			x_offset += .01f;
		}
		else {
			x_offset = 0.99f;
		}
		});
}

bool boundsCheck(float pos)
{
	if (pos > 1.0f || pos < -1.0)
	{
		return true;
	}
	return false;
}

float randomPoint()
{
	return randomFloat(-1.0f, 1.0f);
}


float randomFloat(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution <> dis(min, max);

	return dis(gen);
}

void on_up(GLFWwindow* window, std::function<void()> callback) {
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP)) {
		callback();
	}
}

void on_down(GLFWwindow* window, std::function<void()> callback) {
	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN)) {
		callback();
	}
}

void on_left(GLFWwindow* window, std::function<void()> callback) {
	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT)) {
		callback();
	}
}

void on_right(GLFWwindow* window, std::function<void()> callback) {
	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT)) {
		callback();
	}
}

