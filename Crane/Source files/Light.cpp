#include "Light.h"

const float LIGHTCHANGE = 0.15f;

Light::Light(glm::vec3 colour, float value) : ambientColour(colour), ambientValue(value)
{
	lights.push_back(LightSource());
}

Light::~Light() {}

glm::vec3 Light::getAmbient()
{
	return ambientColour * ambientValue;
}

void Light::setAmbientValue(float val)
{
	if (val >= 0.0f and val <=1.0f) ambientValue = val;
}

void Light::setAmbientColour(float R, float G, float B)
{
	if (R >= 0.0f && G >= 0.0f && B >= 0.0f && R <= 1.0f && G <= 1.0f && B <= 1.0f) ambientColour = glm::vec3(R, G, B);
}

void Light::addSource(LightSource* source)
{
	lights.push_back(*source);
}

void Light::ProcessKeyboard(Light_Change change, double deltaTime)
{
	float changespeed = LIGHTCHANGE * deltaTime;
	if (change == AMBIENTUP) {
		setAmbientValue(ambientValue + changespeed);
	}
	else if (change == AMBIENTDOWN) {
		setAmbientValue(ambientValue - changespeed);
	}
	else if (change == VALUP) {
		lights[0].setValue(std::min(1.0f, lights[0].getValue().x + changespeed), std::min(1.0f, lights[0].getValue().y + changespeed), std::min(1.0f, lights[0].getValue().z + changespeed));
	}
	else if (change == VALDOWN) {
		lights[0].setValue(std::max(0.0f, lights[0].getValue().x - changespeed), std::max(0.0f, lights[0].getValue().y - changespeed), std::max(0.0f, lights[0].getValue().z - changespeed));
	}
	else if (change == RUP) {
		lights[0].setValue(std::min(1.0f, lights[0].getValue().x + changespeed), lights[0].getValue().y, lights[0].getValue().z);
	}
	else if (change == RDOWN) {
		lights[0].setValue(std::max(0.0f, lights[0].getValue().x - changespeed), lights[0].getValue().y, lights[0].getValue().z);
	}
	else if (change == GUP) {
		lights[0].setValue(lights[0].getValue().x, std::min(1.0f, lights[0].getValue().y + changespeed), lights[0].getValue().z);
	}
	else if (change == GDOWN) {
		lights[0].setValue(lights[0].getValue().x, std::max(0.0f, lights[0].getValue().y - changespeed), lights[0].getValue().z);
	}
	else if (change == BUP) {
		lights[0].setValue(lights[0].getValue().x, lights[0].getValue().y, std::min(1.0f, lights[0].getValue().z + changespeed));
	}
	else if (change == BDOWN) {
		lights[0].setValue(lights[0].getValue().x, lights[0].getValue().y, std::max(0.0f, lights[0].getValue().z - changespeed));
	}
}