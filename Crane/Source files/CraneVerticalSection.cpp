#include "CraneVerticalSection.h"

CraneVerticalSection::CraneVerticalSection(unsigned int numberOfParts, const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture* beamText, Texture* weightText)
	:part(new CraneVerticalSectionPart*[numberOfParts]), numberOfParts(numberOfParts), topCube(vertexPath, fragmentPath, 1.0f, 0.2f, 1.0f), baseCube(vertexPath, fragmentPath, 2.2f, 0.1f, 4.5f), weight(vertexPath, fragmentPath, 1.5f, 1.0f, 1.0f)
{
	GLfloat nexty = 1.1f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		part[i] = new CraneVerticalSectionPart(vertexPath, fragmentPath, verticesPath, indicesPath, beamText);

		if (i != 0) {
			part[i]->trans.move(0.0f, nexty, 0.0f);
			part[i]->transTilt.move(0.0f, nexty, 0.0f);
			++nexty;
		}
	}

	topCube.generateObject();
	topCube.trans.moveAndRun(0.0f, nexty, -0.1f);
	baseCube.generateObject();
	baseCube.trans.moveAndRun(0.0f, 0.0f, -0.1f);
	weight.generateObject();
	weight.trans.moveAndRun(0.0f, 0.1f, -1.1f);
}

CraneVerticalSection::CraneVerticalSection(unsigned int numberOfParts, const Shader& shader, const char* verticesPath, const char* indicesPath, Texture* beamText, Texture* weightText)
	:part(new CraneVerticalSectionPart* [numberOfParts]), numberOfParts(numberOfParts), topCube(shader, beamText, 1.0f, 0.2f, 1.0f), baseCube(shader, beamText, 2.2f, 0.1f, 4.5f), weight(shader, weightText, 1.3f, 1.3f, 1.0f)
{
	GLfloat nexty = 1.1f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		part[i] = new CraneVerticalSectionPart(shader, verticesPath, indicesPath, beamText);

		if (i != 0) {
			part[i]->trans.move(0.0f, nexty, 0.0f);
			part[i]->transTilt.move(0.0f, 0.7f*nexty, -0.7f*nexty);
			++nexty;
		}
	}

	topCube.setTextGen(true);
	topCube.setNormalGen(true);
	topCube.generateObject();
	topCube.trans.moveAndRun(0.0f, nexty, -0.1f);
	baseCube.setTextGen(true);
	baseCube.setNormalGen(true);
	baseCube.generateObject();
	baseCube.trans.moveAndRun(0.0f, 0.0f, -0.1f);
	weight.setTextGen(true);
	weight.setNormalGen(true);
	weight.generateObject();
	weight.trans.moveAndRun(0.0f, 0.1f, -1.6f);
}

CraneVerticalSection::~CraneVerticalSection()
{
	for (unsigned int i = 0; i < numberOfParts; ++i) delete part[i];
	delete[] part;
}


void CraneVerticalSection::render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos)
{
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->render(view, zoom);
	topCube.render(view, zoom, ambient, light, lightPos, cameraPos);
	baseCube.render(view, zoom, ambient, light, lightPos, cameraPos);
	weight.render(view, zoom, ambient, light, lightPos, cameraPos);
	weight.trans.moveAndRun(0.0f, 0.0f, 3.0f);
	weight.render(view, zoom, ambient, light, lightPos, cameraPos);
	weight.trans.moveAndRun(0.0f, 0.0f, -3.0f);
}

unsigned int CraneVerticalSection::partsNumber() {
	return numberOfParts;
}