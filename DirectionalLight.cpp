#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(const DirectionalLight& other):Light(other)
{
	direction = other.direction;
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
								   GLfloat aIntensity, GLfloat dIntensity,
								   GLfloat xDir, GLfloat yDir, GLfloat zDir):Light(red,green,blue,aIntensity,dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

DirectionalLight::DirectionalLight(glm::vec3 Ncolour, GLfloat aIntensity, glm::vec3 Dir, GLfloat dIntensity) :Light(Ncolour,aIntensity,dIntensity)
{
	direction = Dir;
}

void DirectionalLight::useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
	unsigned int diffuseIntensityLocation, unsigned int diffuseDirectionLocation)
{
	glUniform3f(ambientColourLocation, colour.r, colour.g, colour.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(diffuseDirectionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}

DirectionalLight::~DirectionalLight()
{
}
