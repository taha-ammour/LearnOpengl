#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

const GLint width = 800;
const GLint height = 600;

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;

std::vector<Mesh* > Meshlist;
std::vector<Shader> Shaderlist;

bool direction = true;
float triOffset = 0.0f, triMaxOffset = 0.7f, triIncrement = 0.0005f;
float curAngle = 0.0f;

bool sizeDirection = true;
float currentSize = 0.4f;
float Maxsize = 0.8f, Minsize = 0.1f;


//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//fragment Shader
static const char* fShader = "Shaders/shader.frag";


void CreateOBJ()
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

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateShaderFromFiles(vShader, fShader);
	Shaderlist.push_back(*shader1);
}


int main(int argc, char* argv[]) {

	mainWindow = Window(800, 600);
	mainWindow.initialize();

	CreateOBJ();
	CreateShaders();

	glm::mat4 projection(1.0f);

	GLuint uniformProjection = 0, uniformModel = 0;

	//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
	projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
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

		Shaderlist[0].useShader();
		uniformModel = Shaderlist[0].get_ModelLocation();
		uniformProjection = Shaderlist[0].get_ProjectionLocation();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -3.5f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));


		Meshlist[0]->Render_Mesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}