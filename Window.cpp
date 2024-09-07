#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	xChange = 0.0f;
	yChange = 0.0f;

	memset(keys, 0, sizeof(keys));
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	xChange = 0.0f;
	yChange = 0.0f;
}

int Window::initialize()
{
	if (!glfwInit()) {
		std::cerr << "failed to load glfw !!!" << std::endl;
		glfwTerminate();
		return 1;
	}

	//setup glfw window properties
	//opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = No backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow Forward COMPATIBILITY
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	 mainWindow = glfwCreateWindow(width, height, "trying", NULL, NULL);

	if (!mainWindow)
	{
		std::cerr << "failed to load glew !!!" << std::endl;
		glfwTerminate();
		return 1;

	}

	
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//Handle Callbacks key + mouse events
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow Modern Extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cerr << "failed to load glew !!!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;

	}

	glEnable(GL_DEPTH_TEST);

	//setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			theWindow->keys[key] = true;
		else if (action == GLFW_RELEASE)
			theWindow->keys[key] = false;
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mousedFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mousedFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}


GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
