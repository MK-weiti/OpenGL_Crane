#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource
{
	friend class Light;

	glm::vec3 value;
	glm::vec3 position;

public:
	LightSource(glm::vec3 value = glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3 position = glm::vec3(35.0f, 35.0f, 35.0f));
	~LightSource();

	glm::vec3 getValue();
	void setValue(float, float, float);

	glm::vec3 getPosition();
	void setPosition(float, float, float);
};