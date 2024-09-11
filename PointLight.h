#pragma once
#include "Light.h"

class PointLight :
    public Light
{
protected:
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

    void useLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation,
                  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

    ~PointLight();
};

