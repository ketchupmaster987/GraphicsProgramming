#include "../Include/glad/glad.h"
#include "glfw3.h"
#include "iostream"

#define Z_DEFAULT 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, apos.y, aPos.z, 1.0);\n"
"}\0";

const char * fragmentShaderSource = "version 330 core\n"
"out vec4 FragColor\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.1f, 0.5f, 0.2f, 1.0f)"
"}\0";

//making this comment to test changes

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


	//vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		//process input
		process_input(window);

		//render stuff here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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

	return 0;
}

struct Vert
{
	float x;
	float y;
	float z;

};

struct Triangle
{
	Vert a;
	Vert b;
	Vert c;

	/*Triangle()
	{

	}*/

	Triangle(Vert a, Vert b, Vert c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}


	float* toArray()
	{
		float* vert = new float[9];
		vert[0] = this->a.x;
		vert[1] = this->a.y;
		vert[2] = this->a.z;

		vert[3] = this->b.x;
		vert[4] = this->b.y;
		vert[5] = this->b.z;

		vert[6] = this->c.x;
		vert[7] = this->c.y;
		vert[8] = this->c.z;

		return vert;
	}
};

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
}