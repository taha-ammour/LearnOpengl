#pragma once

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	GLfloat lastX, lastY, xChange, yChange;
	bool mousedFirstMoved;

	bool keys[1024];

	void createCallbacks();
	static void handleKeys(GLFWwindow* window,int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	GLint getBufferWidth()  { return bufferWidth;  }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getsKeys() { return keys; }

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

};

