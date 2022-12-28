#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 startPos, glm::vec3 startDir)
	: pos{startPos}, direction{startDir}
{

}

Camera::~Camera()
{

}

void Camera::calcViewMatrix()
{
	viewMat = glm::lookAt(pos, glm::vec3(pos.x, pos.y, 0.0), up); // it's actually a lot simpler than i thought	
}

void Camera::calcProjectionMatrix()
{
	// Under orthographic projection, we are simply defining the cuboid from the camera forwards
	// Thus the fatter/taller the cuboid, the more we view and render into the screen => zoomed out
	projMat = glm::ortho(-xzoom, xzoom, -yzoom, yzoom, 0.0f, 100.0f);
}

void Camera::keyControl(bool *keys, glm::vec4 &dataLimits)
{
	// WSAD to move around (for now)
	if (keys[GLFW_KEY_W])
		pos += glm::vec3(0.0f, getYSpan() * 0.01f, 0.0f);

	if (keys[GLFW_KEY_S])
		pos += glm::vec3(0.0f, getYSpan() -0.01f, 0.0f);

	if (keys[GLFW_KEY_A])
		pos += glm::vec3(getXSpan() * -0.01f, 0.0f, 0.0f);

	if (keys[GLFW_KEY_D])
		pos += glm::vec3(getXSpan() * 0.01f, 0.0f, 0.0f);

	// Zooming
	if (keys[GLFW_KEY_Q])
	{
		if (keys[GLFW_KEY_LEFT_SHIFT]) // x-only modifier
			xzoom = xzoom <= 0 ? xzoom : xzoom * 0.9;

		else if (keys[GLFW_KEY_LEFT_CONTROL]) // y-only modifier
			yzoom = yzoom <= 0 ? yzoom : yzoom * 0.9;

		else // do both
		{
			xzoom = xzoom <= 0 ? xzoom : xzoom * 0.9;
			yzoom = yzoom <= 0 ? yzoom : yzoom * 0.9;
		}
			
	}

	if (keys[GLFW_KEY_E])
	{
		if (keys[GLFW_KEY_LEFT_SHIFT]) // x-only modifier
			xzoom *= 1.1;

		else if (keys[GLFW_KEY_LEFT_CONTROL]) // y-only modifier
			yzoom *= 1.1;

		else // do both
		{
			xzoom *= 1.1;
			yzoom *= 1.1;
		}
	}
		
	// Fit to data
	if (keys[GLFW_KEY_F])
	{
		pos[0] = (dataLimits[0] + dataLimits[1]) / 2.0f;
		pos[1] = (dataLimits[2] + dataLimits[3]) / 2.0f;
		xzoom = (dataLimits[1] - dataLimits[0]) / 2.0f;
		yzoom = (dataLimits[3] - dataLimits[2]) / 2.0f;
	}



}

void Camera::update(bool *keys, glm::vec4 &dataLimits)
{
	// Fill in all the computations here
	keyControl(keys, dataLimits);

	// At the end, compute the new view and projection matrix
	calcViewMatrix();
	calcProjectionMatrix();
	
	// Combine them
	vpMat = projMat * viewMat;

}



// Camera::Camera() {

// }

// Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
// 	position = startPosition;
// 	worldUp = startUp;
// 	yaw = startYaw;
// 	pitch = startPitch;
// 	front = glm::vec3(0.0f, 0.0f, -1.0f);

// 	moveSpeed = startMoveSpeed;
// 	turnSpeed = startTurnSpeed;

// 	update();
// }

// void Camera::keyControl(bool* keys, GLfloat deltaTime) {

// 	GLfloat velocity = moveSpeed * deltaTime;

// 	if (keys[GLFW_KEY_W]) {
// 		position += front * velocity;
// 	}
// 	if (keys[GLFW_KEY_S]) {
// 		position -= front * velocity;
// 	}
// 	if (keys[GLFW_KEY_A]) {
// 		position -= right * velocity;
// 	}
// 	if (keys[GLFW_KEY_D]) {
// 		position += right * velocity;
// 	}
// }

// void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
// 	xChange *= turnSpeed;
// 	yChange *= turnSpeed;

// 	yaw += xChange;
// 	pitch += yChange;

// 	if (pitch > 89.0f) {
// 		pitch = 89.0f;
// 	}

// 	if (pitch < -89.0f) {
// 		pitch = -89.0f;
// 	}

// 	update(); //updates the front
// }

// glm::mat4 Camera::calculateViewMatrix() {
// 	return glm::lookAt(position, position + front, up);
// }

// glm::vec3 Camera::getCameraPosition() {
// 	return position;
// }

// glm::vec3 Camera::getCameraDirection() {
// 	return glm::normalize(front);
// }

// void Camera::update() {
// 	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	front.y = sin(glm::radians(pitch));
// 	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	front = glm::normalize(front);

// 	right = glm::normalize(glm::cross(front, worldUp));
// 	up = glm::normalize(glm::cross(right, front));
// }

// Camera::~Camera() {

// }   