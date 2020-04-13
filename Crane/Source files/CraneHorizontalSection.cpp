#include "CraneHorizontalSection.h"

const glm::vec3 ORANGE = glm::vec3(1.0f, 0.5f, 0.2f);
const glm::vec3 GREY = glm::vec3(0.76f, 0.76f, 0.76f);
const glm::vec3	SKY_BLUE = glm::vec3(0.6f, 0.75f, 0.91f);

CraneHorizontalSection::CraneHorizontalSection(float height, unsigned int numberOfParts, const Shader& texShader,
	Texture* concreteTexture, Texture* beamTexture, Texture* glassTexture, Texture* metalTexture, const char* partVerticesPath, const char* partIndicesPath,
	const char* baseVerticesPath, const char* baseIndicesPath, const char* endVerticesPath, const char* endIndicesPath,	const char* midVerticesPath,
	const char* midIndicesPath, const char* cabinVerticesPath, const char* cabinIndicesPath, const char* atachVerticesPath, const char* atachIndicesPath,
	const char* weightVerticesPath, const char* weightIndicesPath, const char* basketVerticesPath, const char* basketIndicesPath, const char* cabinGlassVerticesPath,
	const char* cabinGlassIndicesPath) :part(new CraneHorizontalSectionTexturedPart*[numberOfParts]),
	numberOfParts(numberOfParts),
	base(texShader, beamTexture, baseVerticesPath, baseIndicesPath),
	end(texShader, beamTexture, endVerticesPath, endIndicesPath, GL_LINE),
	middlePart(texShader, beamTexture, midVerticesPath, midIndicesPath, GL_LINE),
	cabin(texShader, metalTexture, cabinVerticesPath, cabinIndicesPath),
	atachment(texShader, beamTexture, atachVerticesPath, atachIndicesPath, GL_LINE),
	counterweight(texShader, concreteTexture, weightVerticesPath, weightIndicesPath),
	basket(texShader, beamTexture, basketVerticesPath, basketIndicesPath),
	cabinGlass(texShader, glassTexture, cabinGlassVerticesPath, cabinGlassIndicesPath)
{
	counterweight.trans.move(-1.7f, height, -0.1f);
	atachment.trans.move(-1.0f, height + 0.25f, -0.1f);
	basket.trans.move(-1.7f, height + 0.2f, -0.1f);
	base.trans.move(0.0f, height, -0.1f);
	cabin.trans.move(0.0f, height, -1.1f);
	cabinGlass.trans.move(0.0f, height, -1.1f);
	GLfloat nextx = 1.0f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		part[i] = new CraneHorizontalSectionTexturedPart(texShader, beamTexture, partVerticesPath, partIndicesPath, GL_LINE);
		part[i]->trans.move(nextx++, height + 0.25f, -0.1f);
	}
	end.trans.move(nextx, height + 0.25f, -0.1f);
	middlePart.trans.move(0.0f, height + 0.25f, -0.1f);
}

CraneHorizontalSection::~CraneHorizontalSection()
{
	for (unsigned int i = 0; i < numberOfParts; ++i) delete part[i];
	delete[] part;
}


void CraneHorizontalSection::render(glm::mat4 view, float zoom, glm::vec3 light)
{
	counterweight.render(view, zoom, light);
	basket.render(view, zoom, light);
	atachment.render(view, zoom, light);
	base.render(view, zoom, light);
	cabin.render(view, zoom, light);
	cabinGlass.render(view, zoom, light);
	middlePart.render(view, zoom, light);
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->render(view, zoom, light);
	end.render(view, zoom, light);
}

unsigned int CraneHorizontalSection::partsNumber() { return numberOfParts; }

void CraneHorizontalSection::rotate(float angle)
{
	counterweight.rotate(angle);
	basket.rotate(angle);
	atachment.rotate(angle);
	base.rotate(angle);
	cabin.rotate(angle);
	cabinGlass.rotate(angle);
	middlePart.rotate(angle);
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->rotate(angle);
	end.rotate(angle);
}