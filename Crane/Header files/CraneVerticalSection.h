#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CraneVerticalSectionPart.h"
#include "ShaderContainer.h"
#include "Cuboid.h"

class CraneVerticalSection
{
	CraneVerticalSectionPart **part;
	unsigned int numberOfParts;
	Cuboid topCube, baseCube, weight;

public:
	//CraneVerticalSection(unsigned int numberOfParts, const char* vertexPath, const char* fragmentPath);

	CraneVerticalSection(unsigned int numberOfParts, \
		const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture* beamText, Texture* weightText);
	~CraneVerticalSection();

	CraneVerticalSection(unsigned int numberOfParts, \
		const Shader& shader, const char* verticesPath, const char* indicesPath, Texture* beamText, Texture* weightText);

	unsigned int partsNumber();

	void render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos);
};

