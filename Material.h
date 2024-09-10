#pragma once

#include <gl/glew.h>

class Material
{
private:
	GLfloat specularIntensity,shininess;
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);

	void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	~Material();
};

