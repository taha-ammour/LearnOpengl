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
#include "Material.h"

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

Material ShinyMaterial;
Material dullMaterial;


//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//fragment Shader
static const char* fShader = "Shaders/shader.frag";


void calcAverageNormals(unsigned int* indicies, unsigned int indiceCount, GLfloat* verticies, unsigned int verticeCount,
						unsigned int vLength  , unsigned int normalOffset) 
{
	for (size_t i = 0; i < indiceCount; i+=3)
	{
		unsigned int in0 = indicies[i] * vLength;
		unsigned int in1 = indicies[i+1] * vLength;
		unsigned int in2 = indicies[i+2] * vLength;

		glm::vec3 v1(verticies[in1] - verticies[in0], verticies[in1 + 1] - verticies[in0 + 1], verticies[in1 + 2] - verticies[in0 + 2]);
		glm::vec3 v2(verticies[in2] - verticies[in0], verticies[in2 + 1] - verticies[in0 + 1], verticies[in2 + 2] - verticies[in0 + 2]);
		glm::vec3 normal = glm::cross(v1,v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		verticies[in0] += normal.x; verticies[in0 + 1] += normal.y; verticies[in0 + 2] += normal.z;
		verticies[in1] += normal.x; verticies[in1 + 1] += normal.y; verticies[in1 + 2] += normal.z;
		verticies[in2] += normal.x; verticies[in2 + 1] += normal.y; verticies[in2 + 2] += normal.z;

	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(verticies[nOffset], verticies[nOffset + 1], verticies[nOffset + 2]);
		vec = glm::normalize(vec);
		verticies[nOffset] = vec.x; verticies[nOffset + 1] = vec.y; verticies[nOffset + 2] = vec.z;
	}
}


void CreateOBJ()
{
	unsigned int indicies[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat verticies[] = {
	//	  x      y      z  |  u     v  |  nx    ny    nz
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, -1.0f,  1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	calcAverageNormals(indicies, 12, verticies, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->Create_Mesh(verticies, indicies, 32, 12);
	Meshlist.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->Create_Mesh(verticies, indicies, 32, 12);
	Meshlist.push_back(obj2);
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateShaderFromFiles(vShader, fShader);
	Shaderlist.push_back(*shader1);
}


int main(int argc, char* argv[]) {

	mainWindow = Window(1024, 600);
	mainWindow.initialize();

	CreateOBJ();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	brickTexture = Texture((char*)"Textures/brick.png");
	brickTexture.loadTexture();
	dirtTexture = Texture((char*)"Textures/dirt.png");
	dirtTexture.loadTexture();

	ShinyMaterial = Material(1.0f,32.0f);
	dullMaterial = Material(0.3f, 4.0f);

	mainLight = Light(1.0f, 0.8f, 0.7f, 0.2f,
					  2.0f, -1.0f, -2.0f, 1.0f);

	//mainLight = Light();

	glm::mat4 projection(1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		   uniformAmbientIntensity = 0, uniformAmbientColor = 0, uniformDiffuseDirection = 0, uniformDiffuseIntensity = 0,
		   uniformSpecularIntensity = 0, uniformShininess = 0;

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
		uniformDiffuseDirection = Shaderlist[0].get_diffuseDirectionLocation();
		uniformDiffuseIntensity = Shaderlist[0].get_diffuseIntensityLocation();
		uniformEyePosition = Shaderlist[0].get_eyePositionLocation();
		uniformSpecularIntensity = Shaderlist[0].get_specularIntensityLocation();
		uniformShininess = Shaderlist[0].get_shininessLocation();

		mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDiffuseDirection);

		//Projection-View | PV
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		//Camera position 
		glUniform3f(uniformEyePosition, camera.get_CameraPosition().x, camera.get_CameraPosition().y, camera.get_CameraPosition().z);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5f));
		//model = glm::rotate(model, 0.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		brickTexture.useTexture();
		ShinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		Meshlist[0]->Render_Mesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -3.5f));
		//model = glm::rotate(model, 0.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		dirtTexture.useTexture();
		dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		Meshlist[1]->Render_Mesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}