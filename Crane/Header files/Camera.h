#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
	// Camera Attributes
	glm::dvec3 position;
	glm::dvec3 front;
	glm::dvec3 up;
	glm::dvec3 right;
	glm::dvec3 worldUp;
	double yaw;
	double pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	void updateCameraVectors();
public:
	Camera();
	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();
	float getZoom();
	void ProcessKeyboard(Camera_Movement direction, double deltaTime);
	void ProcessMouseMovement(double xoffset, double yoffset);
	void ProcessMouseScroll(float yoffset);
};