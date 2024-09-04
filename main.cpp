#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Mesh.h"

const GLint width = 800;
const GLint height = 600;

const float toRadians = 3.14159265f / 180.0;

std::vector<Mesh* > Meshlist;

GLuint Shader, UniformModel, uniformProjection;

bool direction = true;
float triOffset = 0.0f, triMaxOffset = 0.7f, triIncrement = 0.0005f;
float curAngle = 0.0f;

bool sizeDirection = true;
float currentSize = 0.4f;
float Maxsize = 0.8, Minsize = 0.1;


//Vertex Shader
static const char* vShader = "#version 330	\n\
											\n\
layout (location = 0) in vec3 pos;			\n\
											\n\
uniform mat4 Model;									\n\
uniform mat4 Projection;									\n\
											\n\
out vec4 Vcol;									\n\
											\n\
void main()									\n\
{											\n\
											\n\
	gl_Position = Projection * Model * vec4(pos, 1.0);			\n\
											\n\
	Vcol= vec4(clamp(pos,0.0,1.0),1.0); 										\n\
}";


//fragment Shader
static const char* fShader = "#version 330	\n\
											\n\
out vec4 colour;							\n\
											\n\
in vec4 Vcol;										\n\
											\n\
void main()									\n\
{											\n\
	colour = Vcol;							\n\
}";


void CreateTriangle()
{
	unsigned int indicies[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat verticies[] = {
		-1.0, -1.0, 0.0,
		 0.0, -1.0, 1.0,
		 1.0, -1.0, 0.0,
		 0.0,  1.0, 0.0,
	};


	Mesh* obj1 = new Mesh();
	obj1->Create_Mesh(verticies, indicies, 12, 12);
	Meshlist.push_back(obj1);

}

static void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const char* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);

	glCompileShader(theShader);

	GLint result = 0;
	GLchar elog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(theShader, sizeof(elog), NULL, elog);
		std::cerr << "ERROR COMPILE program : " << shaderType << elog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);


}

void compileShaders() {
	Shader = glCreateProgram();
	if (!Shader)
	{
		std::cerr << "failed creating a shader program !!!" << std::endl;
		return;
	}
	AddShader(Shader, vShader, GL_VERTEX_SHADER);
	AddShader(Shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glLinkProgram(Shader);

	glGetProgramiv(Shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(Shader, sizeof(elog), NULL, elog);
		std::cerr << "ERROR Linking program : " << elog << std::endl;
		return;
	}

	glValidateProgram(Shader);

	glGetProgramiv(Shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(Shader, sizeof(elog), NULL, elog);
		std::cerr << "ERROR Validating program : " << elog << std::endl;
		return;
	}

	UniformModel = glGetUniformLocation(Shader, "Model");
	uniformProjection = glGetUniformLocation(Shader, "Projection");


}

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		std::cerr << "failed to load glfw !!!" << std::endl;
		glfwTerminate();
		return 1;
	}

	//setup glfw window properties
	//opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = No backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow Forward COMPATIBILITY
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(width, height, "trying", NULL, NULL);

	if (!window)
	{
		std::cerr << "failed to load glew !!!" << std::endl;
		glfwTerminate();
		return 1;

	}

	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(window, &BufferWidth, &BufferHeight);

	//set context for glew to use
	glfwMakeContextCurrent(window);

	//Allow Modern Extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cerr << "failed to load glew !!!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;

	}

	glEnable(GL_DEPTH_TEST);

	//setup viewport size
	glViewport(0, 0, BufferWidth, BufferHeight);


	CreateTriangle();
	compileShaders();

	glm::mat4 projection(1.0f);

	//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
	projection = glm::perspective(45.0f, (GLfloat)BufferWidth / (GLfloat)BufferHeight, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		//Get + Handle User input Events
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		curAngle += 0.01f;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		if (sizeDirection)
		{
			currentSize += 0.0001f;
		}
		else
		{
			currentSize -= 0.0001f;
		}


		if (currentSize >= Maxsize || currentSize <= Minsize)
		{
			sizeDirection = !sizeDirection;
		}


		//Clear window
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Shader);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -3.5f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));


		Meshlist[0]->Render_Mesh();

		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	return 0;
}