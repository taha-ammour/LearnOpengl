#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}

Light::Light(const Light& other)
{
	colour = other.colour;
	ambientIntensity = other.ambientIntensity;

	direction = other.direction;
	diffuseIntensity = other.diffuseIntensity;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
			 GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	colour = glm::vec3(glm::clamp(red,0.0f,1.0f), glm::clamp(green, 0.0f, 1.0f), glm::clamp(blue, 0.0f, 1.0f));
	ambientIntensity = aIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

Light::Light(glm::vec3 Ncolour, GLfloat aIntensity, glm::vec3 Dir, GLfloat dIntensity)
{
	colour = Ncolour;
	ambientIntensity = aIntensity;
	direction = Dir;
	diffuseIntensity = dIntensity;
}

void Light::useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
					 unsigned int diffuseIntensityLocation, unsigned int diffuseDirectionLocation)
{
	glUniform3f(ambientColourLocation, colour.r, colour.g, colour.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(diffuseDirectionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}

Light::~Light()
{
}
