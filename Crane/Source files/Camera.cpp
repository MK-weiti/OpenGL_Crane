#include "Camera.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

Camera::Camera() 
	: front(glm::vec3(0.0f, 0.0f, 1.0f)), yaw(YAW), pitch(PITCH), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	position = glm::vec3(0.0f, 3.7f, 10.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() { return glm::lookAt(position, position + front, up); }
glm::vec3 Camera::getPosition() { return position; }

float Camera::getZoom() { return zoom; }

void Camera::ProcessKeyboard(Camera_Movement direction, double deltaTime)
{
	double velocity = movementSpeed * deltaTime * (zoom/ZOOM);
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	if (direction == UP)
		position += up * velocity;
	if (direction == DOWN)
		position -= up * velocity;
}

void Camera::ProcessMouseMovement(double xoffset, double yoffset)
{
	xoffset *= mouseSensitivity * (zoom / ZOOM);
	yoffset *= mouseSensitivity * (zoom / ZOOM);

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f)	pitch = -89.0f;

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::dvec3 tmpFront;
	tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tmpFront.y = sin(glm::radians(pitch));
	tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(tmpFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}