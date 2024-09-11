#pragma once
#include "Light.h"

class PointLight :
    public Light
{
private:
    glm::vec3 position;
    
    GLfloat constant, linear, exponent;// c+bx+ax :x = distance
public:
    PointLight();
    PointLight(const PointLight& other);
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
               GLfloat aIntensity, GLfloat dIntensity, 
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat con, GLfloat lin, GLfloat exp);

    PointLight(glm::vec3 Ncolour,
               GLfloat aIntensity, GLfloat dIntensity,
               glm::vec3 pos,
               GLfloat con, GLfloat lin, GLfloat exp);

    void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
                  unsigned int diffuseIntensityLocation, unsigned int positionLocation,
                  unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);

    ~PointLight();
};

