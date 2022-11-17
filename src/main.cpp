#include "Window.h"
#include "Camera.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

int main()
{
    Window mainWindow(1366, 768);
	mainWindow.initialise();

	Camera camera;

	LineItemShader lineItemShader;

	GLuint uniformView = 0;

    // Loop until window closed
	while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime();

		// Get and handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable shaders
		lineItemShader.UseShader();

		// Process the view matrix
		camera.calcViewMatrix(); 

		// Set the uniform view
		uniformView = lineItemShader.GetViewLocation();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

		// unbind
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

    return 0;
}