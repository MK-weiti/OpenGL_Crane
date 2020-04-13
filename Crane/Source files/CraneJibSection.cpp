
#include "CraneJibSection.h"
const glm::vec4 ORANGE = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);
const glm::vec4 BLACK = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
const glm::vec4 LIGHT_BLACK = glm::vec4(0.11f, 0.11f, 0.11f, 1.0f);
const glm::vec4 GREY = glm::vec4(0.70f, 0.70f, 0.70f, 1.0f);
const glm::vec4 SILVER = glm::vec4(1.92f, 1.92f, 1.92f, 1.0f);
float CraneJibSection::linePartCounter = 0.0;
CraneJibSection::CraneJibSection(GLfloat height, unsigned int numberOfParts, const Shader& shader, const Shader& texShader, Texture* texture, Texture* beamTexture, const char* verticesPartPath,
	const char* indicesPartPath, const char* verticesWheelPath, const char* indicesWheelPath, const char* verticesRailPath, const char* indicesRailPath,const char* verticesLinePartPath, const char* indicesLinePartPath, const char* verticesLineEndPath, const char* indicesLineEndPath)
	:railPart(new CraneHorizontalSectionTexturedPart*[numberOfParts*2]),linePart(new CraneJibSectionLine*[height*2]),numberOfRailParts(numberOfParts*2),lineLength((height - 1.0f)*2)
{

	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
		part[i] = new CraneJibSectionPart(texShader,texture, verticesPartPath, indicesPartPath);
	
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)
		topWheel[i] = new CraneJibSectionWheel(shader, verticesWheelPath, indicesWheelPath, LIGHT_BLACK);

	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)
		bottomWheel[i] = new CraneJibSectionWheel(shader, verticesWheelPath, indicesWheelPath, LIGHT_BLACK);

	float nextx = 1.0f;
	for (unsigned int i = 0; i < numberOfRailParts; ++i) {
		if(i==numberOfParts)nextx = 1.0f;
		railPart[i] = new CraneHorizontalSectionTexturedPart(texShader, beamTexture, verticesRailPath, indicesRailPath);
		if(i<numberOfParts)	railPart[i]->trans.move(nextx++, height + 0.25f, 0.15f);
		else railPart[i]->trans.move(nextx++, height + 0.25f, -0.4f);
	}

	for (unsigned int i = 0; i <NUMBEROFLINEPARTS-1; ++i)
		linePart[i] = new CraneJibSectionLine(shader, verticesLinePartPath, indicesLinePartPath, BLACK);//lina

	linePart[NUMBEROFLINEPARTS - 1] = new CraneJibSectionLine(shader, verticesLineEndPath, indicesLineEndPath, SILVER);//hak

	part[0]->trans.scale(1.72f, 1.0f, 0.5f);
	part[0]->trans.move(0.15f, height + 0.2f , -0.049f);
	part[1]->trans.scale(1.72f, 1.0f, 0.5f);
	part[1]->trans.move(0.15f, height + 0.2f , -0.151f);
	int i = 2;
	for (int j = i; i < NUMBEROFJIBPARTS - 4; ++i) 
	{
		part[i]->trans.basicRotate(glm::radians(90.0f), 0.0f, 1.0f, 0.0f);
	}
		part[2]->trans.scale(2.0f, 1.0f, 1.0f);
		part[2]->trans.move(0.7f, height + 0.2f , 0.95f);
		part[3]->trans.scale(2.0f, 1.0f, 1.0f);
		part[3]->trans.move(1.4f, height + 0.2f , 0.95f);
	
		for (int j = i; j < NUMBEROFJIBPARTS; ++j) 
		{
			part[j]->trans.basicRotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
			part[j]->trans.scale(0.4f, 1.0f, 0.5f);
		}
		part[4]->trans.move(0.65f, height + 0.06f, 0.2250001f);
		part[5]->trans.move(0.65f, height + 0.06f, -0.4250001f);
		part[6]->trans.move(1.35f, height + 0.06f, 0.2250001f);
		part[7]->trans.move(1.35f, height + 0.06f, -0.4250001f);
	
	topWheel[0]->trans.move(0.7f + 0.00625f, height + 0.24f + 0.075f, 0.15f);
	topWheel[1]->trans.move(1.4f + 0.00625f, height + 0.24f + 0.075f, 0.15f);
	topWheel[2]->trans.move(0.7f + 0.00625f, height + 0.24f + 0.075f, -0.4f);
	topWheel[3]->trans.move(1.4f + 0.00625f, height + 0.24f + 0.075f, -0.4f);

	bottomWheel[0]->trans.scale(1.5f, 1.5f, 1.0f);
	bottomWheel[1]->trans.scale(1.5f, 1.5f, 1.0f);
	bottomWheel[0]->trans.move(0.925f, height + 0.125f, -0.125f);
	bottomWheel[1]->trans.move(1.175f, height + 0.125f, -0.125f);

	linePart[0]->trans.basicRotate(glm::radians(25.0f), 0.0f, 0.0f, 1.0f);
	linePart[1]->trans.basicRotate(glm::radians(-25.f), 0.0f, 0.0f, 1.0f);
	linePart[0]->trans.scale(1.0f, 1.1f, 1.0f);
	linePart[1]->trans.scale(1.0f, 1.1f, 1.0f);
	linePart[0]->trans.move(1.043f, height-0.359f, -0.1125f);
	linePart[1]->trans.move(1.043f, height-0.353f, -0.1125f);
	
	linePart[2]->trans.move(1.058f, height - 0.35f, -0.1125f);
	linePart[2]->trans.basicRotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
	linePart[2]->trans.scale(1.0f, 0.03, 1.0f);

	linePart[3]->trans.basicRotate(glm::radians(25.0f), 0.0f, 0.0f, 1.0f);
	linePart[4]->trans.basicRotate(glm::radians(-25.0f), 0.0f, 0.0f, 1.0f);
	linePart[3]->trans.scale(1.03f, 0.0f, 1.03f);
	linePart[4]->trans.scale(1.03f, 0.0f, 1.03f);
	linePart[3]->trans.move(1.043f, height - 0.359f, -0.1125f);
	linePart[4]->trans.move(1.043f, height - 0.353f, -0.1125f);

	linePart[NUMBEROFLINEPARTS - 2]->trans.basicRotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
	linePart[NUMBEROFLINEPARTS - 2]->trans.scale(1.0f, lineLength, 1.0f);
	linePart[NUMBEROFLINEPARTS - 2]->trans.move(1.058f, height - 0.365f, -0.1125f);

	linePart[NUMBEROFLINEPARTS-1]->trans.move(1.043f, 1.0f - 0.365f, -0.1125f);	
}


CraneJibSection::~CraneJibSection()
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i) delete part[i];
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)delete bottomWheel[i];
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)delete topWheel[i];
	for (unsigned int i = 0; i < numberOfRailParts; ++i) delete railPart[i];
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i) delete linePart[i];
	//delete[] bottomWheel;
	//delete[] part;
//	delete[] topWheel;
	delete[] linePart;
	delete[] railPart;
}


void CraneJibSection::render(glm::mat4 view, float zoom, glm::vec3 light)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
		if (i >= NUMBEROFJIBPARTS - 4)part[i]->render(view, zoom, light);
		else
		{
			part[i]->render(view, zoom, light);
		}
	}
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i)
	{
	linePart[i]->render(view, zoom, light);
	}
	for (unsigned int i = 0; i < numberOfRailParts; ++i) railPart[i]->render(view, zoom, light);
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->render(view, zoom, light);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)topWheel[i]->render(view, zoom, light);
}

void CraneJibSection::rotate(float angle)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
			part[i]->rotate(angle, 0.0f, 1.0f, 0.0f);	
	}
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i)
	{
		linePart[i]->rotate(angle);
	}
	for (unsigned int i = 0; i < numberOfRailParts; ++i) railPart[i]->rotate(angle);
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->rotate(angle);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)topWheel[i]->rotate(angle);
}

void CraneJibSection::moveJibHorizontally(float movement)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
		part[i]->trans.move(movement, 0.0, 0.0);	
	}
	for (unsigned int i = 0; i <NUMBEROFLINEPARTS; ++i)
	{
			linePart[i]->trans.move(movement, 0.0, 0.0);
	}
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->trans.move(movement, 0.0, 0.0);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)
	{	
		if(movement < 0.0f)topWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, 1.0f);
		if (movement > 0.0f)topWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, -1.0f);	
		topWheel[i]->trans.move(movement, 0.0, 0.0);
	}

}
void CraneJibSection::moveJibVertically(float movement)
{
	if (movement == 0)return;
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)
	{
		if (movement < 0.0f &&  linePartCounter + movement>0.0f)
		{
			if (i % 2 == 0)bottomWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, 1.0f);
			else  bottomWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, -1.0f);
		}
		else if (movement > 0.0f && linePartCounter + movement < lineLength)
		{
			if (i % 2 == 1)bottomWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, 1.0f);
			else bottomWheel[i]->trans.basicRotate(glm::radians(1.2f), 0.0f, 0.0f, -1.0f);

		}
	}

	linePartCounter += movement;
	if (movement > 0.0f)
	{
		if (linePartCounter < lineLength)
			linePart[NUMBEROFLINEPARTS - 1]->trans.move(0.0f, movement / 2, 0.0f);
		if (linePartCounter > lineLength)
			linePartCounter -= movement;
	}
	else if (movement < 0.0f)
	{
		if (linePartCounter > 0.0f)
			linePart[NUMBEROFLINEPARTS - 1]->trans.move(0.0f, movement / 2, 0.0f);
		if (linePartCounter < 0.0f) linePartCounter -= movement;
	}
	linePart[NUMBEROFLINEPARTS - 2]->trans.resetScale();
	linePart[NUMBEROFLINEPARTS - 2]->trans.scale(1.0f, lineLength - linePartCounter, 1.0f);
	
	float temp = linePartCounter;
	while (temp > 1.1f)temp -= 1.1f;
	linePart[3]->trans.resetScale();
	linePart[4]->trans.resetScale();
	linePart[3]->trans.scale(1.03f, temp, 1.03f);
	linePart[4]->trans.scale(1.03f,temp, 1.03f);
}