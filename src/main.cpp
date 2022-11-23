#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include <vector>

int main(int argc, char *argv[])
{
    Window mainWindow(640, 480);
	mainWindow.initialise();

	Camera camera;

	PlotShader lineItemShader;

	LineMesh lineMesh;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	// Default test
	if (argc == 1)
	{
		vertices = std::vector<GLfloat>{
			0.0f, 1.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f
		};
		indices = std::vector<unsigned int>{
			0,1,
			1,2
		};
		lineMesh.CreateMesh(vertices.data(), indices.data(), 3*3, 2*2);
	}
	else{
		return 1; // TODO, configure number of points passed in with random gen
	}

	// GLuint uniformView = 0;
	GLuint uniformVp = 0;

    // Loop until window closed
	GLfloat now, prev = 0;
	while (!mainWindow.getShouldClose()) {
		now = glfwGetTime();

		// Diagnostics for FPS?
		printf("FPS: %.2f\n", 1/(now-prev));
		prev = now;

		// Get and handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable shaders
		lineItemShader.UseShader();

		// Do all the camera work (also processes the new frame's view matrix)
		camera.update(mainWindow.getKeys());

		// Set the uniform view
		// uniformView = lineItemShader.GetViewLocation();
		uniformVp = lineItemShader.GetVpLocation();
		// glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
		glUniformMatrix4fv(uniformVp, 1, GL_FALSE, glm::value_ptr(camera.getVpMatrix()));

		// Render things
		lineMesh.RenderMesh();

		// unbind
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

    return 0;
}