#include "LightSource.h"

LightSource::LightSource(glm::vec3 value, glm::vec3 position) : value(value), position(position)
{

}

LightSource::~LightSource() {}

void LightSource::setValue(float r, float g, float b)
{
	value = glm::vec3(r, g, b);
}

glm::vec3 LightSource::getValue()
{
	return value;
}

void LightSource::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

glm::vec3 LightSource::getPosition()
{
	return position;
}