#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light
{
private:
	//ambient lighting
	glm::vec3 colour;
	GLfloat ambientIntensity;
	
	// Diffuse lighting
	glm::vec3 direction;
	GLfloat diffuseIntensity;

public:
	Light();

	Light(const Light& other);

	Light(GLfloat red , GLfloat green, GLfloat blue, GLfloat aIntensity,
		  GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	Light(glm::vec3 Ncolour,GLfloat aIntensity, glm::vec3 Dir, GLfloat dIntensity);

	void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
				  unsigned int diffuseIntensityLocation, unsigned int diffuseDirectionLocation);

	~Light();
};

