#pragma once
#include "CraneJibSectionPart.h"
#include "CraneJibSectionWheel.h"
#include "CraneJibSectionLine.h"
#include "CraneHorizontalSectionTexturedPart.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
const unsigned static int NUMBEROFJIBPARTS = 8;
const unsigned static int NUMBEROFJIBTOPWHEELS = 4;
const unsigned static int NUMBEROFJIBBOTTOMWHEELS = 2;
const unsigned static int NUMBEROFLINEPARTS = 7;//0,1 -konstrukcja , 2,3-lina ,4 - hak
class CraneJibSection
{
	CraneJibSectionPart *part[NUMBEROFJIBPARTS];
	CraneJibSectionLine **linePart;
	CraneJibSectionWheel *topWheel[NUMBEROFJIBTOPWHEELS];
	CraneJibSectionWheel *bottomWheel[NUMBEROFJIBBOTTOMWHEELS];
	CraneHorizontalSectionTexturedPart **railPart;
	unsigned int numberOfRailParts;
	static float linePartCounter;
	float lineLength;
public:
	CraneJibSection(GLfloat height, unsigned int numberOfParts, const Shader& shader, const Shader& texShader, Texture* texture, Texture* beamTexture, const char* verticesPartPath,
		const char* indicesPartPath, const char* verticesWheelPath, const char* indicesWheelPath,const char* verticesRailPath, const char* indicesRailPath, const char* verticesLinePartPath, const char* indicesLinePartPath, const char* verticesLineEndPath, const char* indiceslineEndPath);
	~CraneJibSection();


	void render(glm::mat4 view, float zoom, glm::vec3 light);
	void moveJibHorizontally(float movement);
	void moveJibVertically(float movement);
	void rotate(float angle);
};

