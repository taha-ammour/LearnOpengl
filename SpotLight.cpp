#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	direction = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(const SpotLight& other): PointLight(other)
{
	direction = other.direction;
	edge = other.edge;
	procEdge = other.procEdge;
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
					 GLfloat aIntensity, GLfloat dIntensity,
					 GLfloat xPos, GLfloat yPos, GLfloat zPos,
					 GLfloat xDir, GLfloat yDir, GLfloat zDir,
					 GLfloat con, GLfloat lin, GLfloat exp,
					 GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(glm::vec3 Ncolour,
					 GLfloat aIntensity, GLfloat dIntensity,
					 glm::vec3 pos, glm::vec3 position, glm::vec3 Directio,
					 GLfloat con, GLfloat lin, GLfloat exp,
					 GLfloat edg) : PointLight(Ncolour,aIntensity,dIntensity,pos,con,lin,exp)
{
	direction = glm::normalize(Directio);
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
						 GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
						 GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
						 GLuint edgeLocation)
{
	glUniform3f(ambientColourLocation, colour.r, colour.g, colour.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);

	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

void SpotLight::setFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}

SpotLight::~SpotLight()
{
}
