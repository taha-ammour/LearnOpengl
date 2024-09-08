#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;// x-axis:left/right
	GLfloat pitch;// y-axis:up/down

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void update();

public:
	Camera();

	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	
	void keyControls(bool* keys, GLfloat deltaTime);
	void mouseControls(GLfloat xChange, GLfloat yChange);


	glm::mat4 CalculateViewMatrix();
	
	~Camera();

};

