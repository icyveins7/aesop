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

	// Getters
	inline glm::vec3& getPos(){ return pos; }
	inline glm::vec3& getDirection(){ return direction; }
	inline glm::mat4& getViewMatrix(){ return viewMat; }
	inline glm::mat4& getProjectionMatrix(){ return projMat; }
	inline glm::mat4& getVpMatrix(){ return vpMat; }

	// Setters
	inline void setZoom(float new_zoom){zoom = new_zoom;}

	// Computations
	void calcViewMatrix();
	void calcProjectionMatrix();
	void keyControl(bool *keys);
	void update(bool *keys);

private:
	glm::vec3 pos;
	glm::vec3 direction;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	glm::mat4 vpMat;
	float zoom = 1.0;

	// this is constant since we're in orthographic projection
	// note that this represents the y-axis of the camera (recall that screen is in x-y, z is out of screen)
	// hence up should be parallel to y-axis, in order for the image to not be rotated
	const glm::vec3 up = {0.0f, 1.0f, 0.0f}; 

	// Scaling movement
	float getXSpan(){ return 2 * zoom; }
	float getYSpan(){ return 2 * zoom; } // these will change eventually

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

