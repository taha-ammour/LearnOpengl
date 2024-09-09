#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	colour = glm::vec3(glm::clamp(red,0.0f,1.0f), glm::clamp(green, 0.0f, 1.0f), glm::clamp(blue, 0.0f, 1.0f));
	ambientIntensity = aIntensity;
}

Light::Light(glm::vec3 Ncolour, GLfloat aIntensity)
{
	colour = Ncolour;
	ambientIntensity = aIntensity;
}

void Light::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation)
{
	glUniform3f(ambientColourLocation, colour.r, colour.g, colour.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
}

Light::~Light()
{
}
