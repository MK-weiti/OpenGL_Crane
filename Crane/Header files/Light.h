#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include "LightSource.h"

enum Light_Change {
	VALUP,
	VALDOWN,
	RUP,
	RDOWN,
	GUP,
	GDOWN,
	BUP,
	BDOWN,
	AMBIENTUP,
	AMBIENTDOWN
};

class Light 
{
	float ambientValue;
	glm::vec3 ambientColour;
	
public:
	std::vector<LightSource> lights;

	Light(glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f), float value = 0.7f);
	~Light();

	glm::vec3 getAmbient();
	void setAmbientValue(float);
	void setAmbientColour(float, float, float);
	void addSource(LightSource*);
	void ProcessKeyboard(Light_Change change, double deltaTime);
};