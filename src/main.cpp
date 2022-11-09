#include "Window.h"

int main()
{
    Window mainWindow(1366, 768);
	mainWindow.initialise();

    // Loop until window closed
	while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime();

		// Get and handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainWindow.swapBuffers();
	}

    return 0;
}