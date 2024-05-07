#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <random>
//#include <algorithm>

void generateIndices(std::vector<unsigned int> &indices, int numPts)
{
    // For n points, there are n-1 segments
    indices.resize((numPts-1)*2);
    // Simply increment
    for (int i = 0; i < indices.size() / 2; i++)
    {
        indices.at(i*2 + 0) = i;
        indices.at(i*2 + 1) = i + 1;
    }
}

glm::vec4 getDataLimits(std::vector<GLfloat>& vertices)
{
    // Assumed 3d vertices
    int numPts = (int)vertices.size() / 3;

    // Initialise to the first value
    GLfloat xmin = vertices.at(0);
    GLfloat xmax = vertices.at(0);
    GLfloat ymin = vertices.at(1);
    GLfloat ymax = vertices.at(1);

    // Simple loop
    for (int i = 1; i < numPts; i++)
    {
        xmin = vertices.at(i * 3 + 0) < xmin ? vertices.at(i * 3 + 0) : xmin;
        xmax = vertices.at(i * 3 + 0) > xmax ? vertices.at(i * 3 + 0) : xmax;
        ymin = vertices.at(i * 3 + 1) < ymin ? vertices.at(i * 3 + 1) : ymin;
        ymax = vertices.at(i * 3 + 1) > ymax ? vertices.at(i * 3 + 1) : ymax;
    }

    return glm::vec4(xmin, xmax, ymin, ymax);
}

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
    }
    else{
        int numPts = atoi(argv[1]);
        printf("Using %d points \n", numPts);

        float step = 0.001;

        vertices.resize(numPts * 3);
        for (int i = 0; i < numPts; i++){
        	vertices.at(i*3 + 0) = step * i; // x
        	vertices.at(i*3 + 1) = sinf(step*i); // y
        	vertices.at(i*3 + 2) = 0.0f;
        }

        // automatically generate contiguous indices
        generateIndices(indices, numPts);
    }

    // Create the mesh
    lineMesh.CreateMesh(
        vertices.data(), indices.data(),
        (int)vertices.size(),
        (int)indices.size()
    );
    // Generate bounds for plotting camera later
    glm::vec4 dataLimits = getDataLimits(vertices);
    printf("Data limits are (%f, %f, %f, %f)\n", dataLimits[0], dataLimits[1], dataLimits[2], dataLimits[3]);

    // GLuint uniformView = 0;
    GLuint uniformVp = 0;

    // Loop until window closed
    GLfloat now, prev = 0;
    while (!mainWindow.getShouldClose()) {
        now = glfwGetTime();

        // Diagnostics for FPS?
        //printf("FPS: %.2f\n", 1/(now-prev));
        prev = now;

        // Get and handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable shaders
        lineItemShader.UseShader();

        // Do all the camera work (also processes the new frame's view matrix)
        camera.update(mainWindow.getKeys(), dataLimits, mainWindow.getXChange(), mainWindow.getYChange(), mainWindow.getYScroll());

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
