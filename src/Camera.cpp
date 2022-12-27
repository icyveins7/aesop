#include "Camera.h"

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
	projMat = glm::ortho(-zoom, zoom, -zoom, zoom, 0.0f, 100.0f);
}

void Camera::keyControl(bool *keys)
{
	// WSAD to move around (for now)
	if (keys[GLFW_KEY_W])
		pos += glm::vec3(0.0f, 0.1f, 0.0f);

	if (keys[GLFW_KEY_S])
		pos += glm::vec3(0.0f, -0.1f, 0.0f);

	if (keys[GLFW_KEY_A])
		pos += glm::vec3(-0.1f, 0.0f, 0.0f);

	if (keys[GLFW_KEY_D])
		pos += glm::vec3(0.1f, 0.0f, 0.0f);

	if (keys[GLFW_KEY_Q])
		zoom = zoom <= 0 ? zoom : zoom * 0.9;

	if (keys[GLFW_KEY_E])
		zoom *= 1.1;

}

void Camera::update(bool *keys)
{
	// Fill in all the computations here
	keyControl(keys);

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