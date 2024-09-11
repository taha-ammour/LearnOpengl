#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(const Light& other)
{
	colour = other.colour;
	ambientIntensity = other.ambientIntensity;
	diffuseIntensity = other.diffuseIntensity;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	colour = glm::vec3(glm::clamp(red,0.0f,1.0f), glm::clamp(green, 0.0f, 1.0f), glm::clamp(blue, 0.0f, 1.0f));
	ambientIntensity = aIntensity;

	diffuseIntensity = dIntensity;
}

Light::Light(glm::vec3 Ncolour, GLfloat aIntensity, GLfloat dIntensity)
{
	colour = Ncolour;
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}


Light::~Light()
{
}
