#include "CraneVerticalSectionPart.h"

CraneVerticalSectionPart::CraneVerticalSectionPart(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture* beamText)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader), transTilt(shader), cylinder(shader, beamText, 1, 0.05f, 2, 4)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transTilt.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transTilt.scaleAndRun(1.0f, 1.0f, 1.45f);

	cylinder.setTextGen(true);
	cylinder.generateObject();
}

CraneVerticalSectionPart::CraneVerticalSectionPart(const Shader& shader, const char* verticesPath, const char* indicesPath, Texture* beamText)
	:shader(shader), vertices(verticesPath, indicesPath), trans(this->shader), transTilt(this->shader), cylinder(shader, beamText, 1, 0.05f, 2, 4)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transTilt.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transTilt.scaleAndRun(1.0f, 1.0f, 1.45f);

	cylinder.setTextGen(true);
	cylinder.generateObject();
}

//CraneVerticalSectionPart::CraneVerticalSectionPart(const char* vertexPath, const char* fragmentPath)
//	:shader(shader), trans(this->shader)
//{
//	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
//}

CraneVerticalSectionPart::~CraneVerticalSectionPart() {}

void CraneVerticalSectionPart::render(glm::mat4 view, float zoom)
{
	//shader.use();

	//trans.runAll();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//vertices.draw(true);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//horizontal
	cylinder.trans = trans;
	cylinder.trans.moveAndRun(-0.45f, 0.0f, -0.6f);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(0.9f, 0.0f, 0.0f);
	cylinder.render(view, zoom);

	cylinder.trans.rotateAndRun(3.14f/2, 0, 1, 0);
	cylinder.trans.moveAndRun(0.15f, 0.0f, 0.1f);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(-1.0f, 0.0f, 0.0f);
	cylinder.render(view, zoom);

	//tilted
	cylinder.trans = transTilt;
	cylinder.trans.moveAndRun(-0.45f, 0.3f, -1.18f);
	cylinder.trans.rotateAndRun(3.14f / 4, 1, 0, 0);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(0.9f, 0.0f, 0.0f);
	cylinder.render(view, zoom);

	cylinder.trans.rotateAndRun(3.14f / 2, 0, 1, -1);
	cylinder.trans.moveAndRun(0.15f, 0.07f, 0.08f);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(-1.0f, 0.0f, 0.0f);
	cylinder.render(view, zoom);

	cylinder.trans.rotateAndRun(3.14f / 2, 0, 1, -1);
	cylinder.trans.moveAndRun(-0.08f, 0.08f, 0.08f);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(0.95f, 0.0f, 0.0f);
	cylinder.render(view, zoom);

	cylinder.trans.rotateAndRun(3 * 3.14f / 2, 0, -1, 1);
	cylinder.trans.moveAndRun(-0.07f, -0.08f, -0.09f);
	cylinder.render(view, zoom);

	cylinder.trans.moveAndRun(-1.0f, 0.0f, 0.0f);
	cylinder.render(view, zoom);
}

