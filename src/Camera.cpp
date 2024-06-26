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
    projMat = glm::ortho(-xzoom/2, xzoom/2, -yzoom/2, yzoom/2, 0.0f, 100.0f);
}

void Camera::keyControl(bool *keys, glm::vec4 &dataLimits)
{
    // WSAD to move around (for now)
    if (keys[GLFW_KEY_W])
        pos += glm::vec3(0.0f, getYSpan() * 0.01f, 0.0f);

    if (keys[GLFW_KEY_S])
        pos += glm::vec3(0.0f, getYSpan() * -0.01f, 0.0f);

    if (keys[GLFW_KEY_A])
        pos += glm::vec3(getXSpan() * -0.01f, 0.0f, 0.0f);

    if (keys[GLFW_KEY_D])
        pos += glm::vec3(getXSpan() * 0.01f, 0.0f, 0.0f);

    // Zooming
    if (keys[GLFW_KEY_Q])
    {
        if (keys[GLFW_KEY_LEFT_SHIFT]) // x-only modifier
            xzoom = xzoom <= 0.0f ? xzoom : xzoom * 0.9f;

        else if (keys[GLFW_KEY_LEFT_CONTROL]) // y-only modifier
            yzoom = yzoom <= 0.0f ? yzoom : yzoom * 0.9f;

        else // do both
        {
            xzoom = xzoom <= 0.0f ? xzoom : xzoom * 0.9f;
            yzoom = yzoom <= 0.0f ? yzoom : yzoom * 0.9f;
        }

    }

    if (keys[GLFW_KEY_E])
    {
        if (keys[GLFW_KEY_LEFT_SHIFT]) // x-only modifier
            xzoom *= 1.1f;

        else if (keys[GLFW_KEY_LEFT_CONTROL]) // y-only modifier
            yzoom *= 1.1f;

        else // do both
        {
            xzoom *= 1.1f;
            yzoom *= 1.1f;
        }
    }

    // Fit to data
    if (keys[GLFW_KEY_F])
    {
        pos[0] = (dataLimits[0] + dataLimits[1]) / 2;
        pos[1] = (dataLimits[2] + dataLimits[3]) / 2;
        xzoom = (dataLimits[1] - dataLimits[0]);
        yzoom = (dataLimits[3] - dataLimits[2]);
    }



}

void Camera::mouseControl(GLfloat xchange, GLfloat ychange)
{
    // scale by the span
    pos[0] -= xchange * getXSpan(); // -= because we want the 'dragging' effect
    pos[1] -= ychange * getYSpan();
}

void Camera::mouseScrollControl(GLfloat yscroll)
{
    // perform a similar zooming function as the Q/E keys, but scaled
    const GLfloat scrollScale = 10.0f; // note that due to division, if scale is bigger then the scroll rate is slower
    xzoom = xzoom * (1.0f - yscroll / scrollScale); // minus is due to convention that scrolling up = zooming in
    yzoom = xzoom * (1.0f - yscroll / scrollScale);
}

void Camera::update(bool *keys, glm::vec4 &dataLimits, GLfloat xchange, GLfloat ychange, GLfloat yscroll)
{
    // Fill in all the computations here
    keyControl(keys, dataLimits);
    mouseControl(xchange, ychange);
    mouseScrollControl(yscroll);

    // At the end, compute the new view and projection matrix
    calcViewMatrix();
    calcProjectionMatrix();

    // Combine them
    vpMat = projMat * viewMat;

}



// Camera::Camera() {

// }

// Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
//     position = startPosition;
//     worldUp = startUp;
//     yaw = startYaw;
//     pitch = startPitch;
//     front = glm::vec3(0.0f, 0.0f, -1.0f);

//     moveSpeed = startMoveSpeed;
//     turnSpeed = startTurnSpeed;

//     update();
// }

// void Camera::keyControl(bool* keys, GLfloat deltaTime) {

//     GLfloat velocity = moveSpeed * deltaTime;

//     if (keys[GLFW_KEY_W]) {
//         position += front * velocity;
//     }
//     if (keys[GLFW_KEY_S]) {
//         position -= front * velocity;
//     }
//     if (keys[GLFW_KEY_A]) {
//         position -= right * velocity;
//     }
//     if (keys[GLFW_KEY_D]) {
//         position += right * velocity;
//     }
// }

// void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
//     xChange *= turnSpeed;
//     yChange *= turnSpeed;

//     yaw += xChange;
//     pitch += yChange;

//     if (pitch > 89.0f) {
//         pitch = 89.0f;
//     }

//     if (pitch < -89.0f) {
//         pitch = -89.0f;
//     }

//     update(); //updates the front
// }

// glm::mat4 Camera::calculateViewMatrix() {
//     return glm::lookAt(position, position + front, up);
// }

// glm::vec3 Camera::getCameraPosition() {
//     return position;
// }

// glm::vec3 Camera::getCameraDirection() {
//     return glm::normalize(front);
// }

// void Camera::update() {
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front = glm::normalize(front);

//     right = glm::normalize(glm::cross(front, worldUp));
//     up = glm::normalize(glm::cross(right, front));
// }

// Camera::~Camera() {

// }   
