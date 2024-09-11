#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
private:
    glm::vec3 direction;

public:

    DirectionalLight();

	DirectionalLight(const DirectionalLight& other);

	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					 GLfloat aIntensity, GLfloat dIntensity,
					 GLfloat xDir, GLfloat yDir, GLfloat zDir);

	DirectionalLight(glm::vec3 Ncolour, GLfloat aIntensity, glm::vec3 Dir, GLfloat dIntensity);

	void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
		unsigned int diffuseIntensityLocation, unsigned int diffuseDirectionLocation);

    ~DirectionalLight();
    
};

