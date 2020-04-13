#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CraneHorizontalSectionTexturedPart.h"


class CraneHorizontalSection
{
	CraneHorizontalSectionTexturedPart counterweight; //przeciwwaga dzwigu
	CraneHorizontalSectionTexturedPart atachment; //czesc miedzy srodkiem a przeciwwaga
	CraneHorizontalSectionTexturedPart basket; //czesc wokol przeciwwagi
	CraneHorizontalSectionTexturedPart base; //podstawa ramienia
	CraneHorizontalSectionTexturedPart cabin; //kabina operatora
	CraneHorizontalSectionTexturedPart cabinGlass; //Szklo w kabinie
	CraneHorizontalSectionTexturedPart **part; //tablica segmentow ramienia
	CraneHorizontalSectionTexturedPart middlePart; //czesc ramienia nad pionem
	CraneHorizontalSectionTexturedPart end; //zakonczenie ramienia
	unsigned int numberOfParts;

public:
	CraneHorizontalSection(float height, unsigned int numberOfParts,
		const Shader& texShader, Texture* ConcreteTexture, Texture* beamTexture,
		Texture* glassTexture, Texture* metalTexture, const char* partVerticesPath, const char* partIndicesPath,
		const char* baseVerticesPath, const char* baseIndicesPath, const char* endVerticesPath, const char* endIndicesPath,
		const char* midVerticesPath, const char* midIndicesPath, const char* cabinVerticesPath, const char* cabinIndicesPath,
		const char* atachVerticesPath, const char* atachIndicesPath, const char* weightVerticesPath, const char* weightIndicesPath,
		const char* basketVerticesPath, const char* basketIndicesPath, const char* cabinGlassVerticesPath, const char* cabinGlassIndicesPath);
	~CraneHorizontalSection();

	unsigned int partsNumber();

	void render(glm::mat4 view, float zoom, glm::vec3 light);
	void rotate(float angle);
};