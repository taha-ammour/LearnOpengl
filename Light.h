#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light
{
protected:
	//ambient lighting
	glm::vec3 colour;
	GLfloat ambientIntensity;
	
	// Diffuse lighting
	GLfloat diffuseIntensity;

public:
	Light();

	Light(const Light& other);

	Light(GLfloat red , GLfloat green, GLfloat blue,
		  GLfloat aIntensity, GLfloat dIntensity);

	Light(glm::vec3 Ncolour,GLfloat aIntensity, GLfloat dIntensity);


	~Light();
};

