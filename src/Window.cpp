#include "Window.h"

Window::Window() {
	width = 400;
	height = 400;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;
}

int Window::initialise() {
	// Initialise GLFW
	if (!glfwInit()) {
		printf("GLFW Init failed.\n");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed.\n");
		glfwTerminate();
		return 2;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Handle key and mouse input
	createCallbacks();
	// glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("glew Init failed.\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 3;
	}

	glEnable(GL_DEPTH_TEST); // for depth-testing

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouseCursor);
	glfwSetScrollCallback(mainWindow, handleMouseScroll);
}

GLfloat Window::getXChange() {
	GLfloat theChange = xChange;
	xChange = 0.0f; // note that this 'consumes' the change
	return theChange;
}

GLfloat Window::getYChange() {
	GLfloat theChange = yChange;
	yChange = 0.0f; // note that this 'consumes' the change
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("Released: %d \n", key);
		}
	}
}

void Window::handleMouseCursor(GLFWwindow* window, double xPos, double yPos)
{
	Window *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = (GLfloat)xPos;
		theWindow->lastY = (GLfloat)yPos;
		theWindow->mouseFirstMoved = false;
	}

	// Update the changes only if button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Note that the callback may fire more often than the consumer, hence we must accumulate changes with +=, otherwise some cursor movement will be 'lost'
		// We also normalise as a fraction of window coords?
		theWindow->xChange += ((GLfloat)xPos - theWindow->lastX) / (GLfloat)(theWindow->getBufferWidth()); // use bufferWidth or width?
		theWindow->yChange += (theWindow->lastY - (GLfloat)yPos) / (GLfloat)(theWindow->getBufferHeight()); // this prevents inversion of up/down camera
	}
	
	theWindow->lastX = (GLfloat)xPos;
	theWindow->lastY = (GLfloat)yPos;
}

void Window::handleMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	// we ignore the xoffset, since most mice don't have it
	theWindow->yScroll += (GLfloat)yoffset; // again, we accumulate instead of setting
}

GLfloat Window::getYScroll()
{
	GLfloat tmp = yScroll;
	yScroll = 0.0f; // consume the change
	return tmp;
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}