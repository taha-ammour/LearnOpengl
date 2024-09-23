#include "PointLight.h"

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.0f,0.0f,0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(const PointLight& other) : Light(other)
{
	position = other.position;
	constant = other.constant;
	linear = other.linear;
	exponent = other.exponent;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
					   GLfloat aIntensity, GLfloat dIntensity,
					   GLfloat xPos, GLfloat yPos, GLfloat zPos,
					   GLfloat con, GLfloat lin, GLfloat exp):Light(red,green,blue,aIntensity,dIntensity)
{
	position = glm::vec3(xPos,yPos,zPos);
	constant = con;
	linear = lin;
	exponent = exp;
}

PointLight::PointLight(glm::vec3 Ncolour,
					   GLfloat aIntensity, GLfloat dIntensity,
					   glm::vec3 pos,
					   GLfloat con, GLfloat lin, GLfloat exp):Light(Ncolour,aIntensity,dIntensity)
{
	position = pos;
	constant = con;
	linear = lin;
	exponent = exp;
}

void PointLight::useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
						  GLuint diffuseIntensityLocation, GLuint positionLocation,
						  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	glUniform3f(ambientColourLocation, colour.r, colour.g, colour.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);

	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);

}

PointLight::~PointLight()
{
}
