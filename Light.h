#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light
{
private:
	glm::vec3 colour;
	GLfloat ambientIntensity;
public:
	Light();
	Light(GLfloat red , GLfloat green, GLfloat blue, GLfloat aIntensity);
	Light(glm::vec3 Ncolour,GLfloat aIntensity);

	void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);

	~Light();
};

