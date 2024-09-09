#define STB_IMAGE_IMPLEMENTATION


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
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

const GLint width = 800;
const GLint height = 600;

const float toRadians = 3.14159265f / 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Window mainWindow;
Camera camera;
Light mainLight;

std::vector<Mesh* > Meshlist;
std::vector<Shader> Shaderlist;

Texture brickTexture;
Texture dirtTexture;

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
	//	  x     y      z  |  u     v
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.5f, 1.0f,
	};


	Mesh* obj1 = new Mesh();
	obj1->Create_Mesh(verticies, indicies, 20, 12);
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

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	brickTexture = Texture((char*)"Textures/brick.png");
	brickTexture.loadTexture();
	dirtTexture = Texture((char*)"Textures/dirt.png");
	dirtTexture.loadTexture();

	mainLight = Light(1.0f, 0.8f, 0.7f, 0.2f);
	//mainLight = Light();

	glm::mat4 projection(1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColor = 0;

	//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
	projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();// SDL_GetPerformanceCounter(); in SDL
		deltaTime = now - lastTime;// (num)*1000/SDL_GetPerformanceFrequency(); 
		lastTime = now;
		//Get + Handle User input Events
		glfwPollEvents();
		camera.keyControls(mainWindow.getsKeys(), deltaTime);
		camera.mouseControls(mainWindow.getXChange(), mainWindow.getYChange());

		//Clear window
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shaderlist[0].useShader();
		uniformModel = Shaderlist[0].get_ModelLocation();
		uniformProjection = Shaderlist[0].get_ProjectionLocation();
		uniformView = Shaderlist[0].get_ViewLocation();
		uniformAmbientColor = Shaderlist[0].get_ambientColorLocation();
		uniformAmbientIntensity = Shaderlist[0].get_ambientIntensityLocation();

		mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		brickTexture.useTexture();
		Meshlist[0]->Render_Mesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}