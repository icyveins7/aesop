#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialise();

	inline GLfloat getWidth() { return width; }
	inline GLfloat getHeight() { return height; }
	inline GLfloat getBufferWidth() { return bufferWidth; }
	inline GLfloat getBufferHeight() { return bufferHeight; }

	inline bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	inline bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	inline void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange, yChange;
	bool mouseFirstMoved;

	void createCallbacks();

	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouseCursor(GLFWwindow* window, double xPos, double yPos);
};

