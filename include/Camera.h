#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera(
		glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3 startDir = glm::vec3(0.0f, 0.0f, -1.0f)
	);
	~Camera();

	glm::vec3& getPos();
	glm::vec3& getDirection();
	glm::mat4& getViewMatrix();

	void calcViewMatrix();
	void update();

private:
	glm::vec3 pos;
	glm::vec3 direction;
	glm::mat4 viewMat;
	const glm::vec3 up = {0.0f, 0.0f, 1.0f}; // this is constant since we're in orthographic projection

};



// class Camera
// {
// public:
// 	Camera();
// 	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

// 	void keyControl(bool* keys, GLfloat deltaTime);
// 	void mouseControl(GLfloat xChange, GLfloat yChange);

// 	glm::vec3 getCameraPosition();
// 	glm::vec3 getCameraDirection();

// 	glm::mat4 calculateViewMatrix();

// 	~Camera();

// private:
// 	glm::vec3 position;
// 	glm::vec3 front;
// 	glm::vec3 up;
// 	glm::vec3 right;
// 	glm::vec3 worldUp;

// 	GLfloat yaw;
// 	GLfloat pitch;

// 	GLfloat moveSpeed;
// 	GLfloat turnSpeed;

// 	void update();
// };

