#include "CraneHorizontalSectionPart.h"

CraneHorizontalSectionPart::CraneHorizontalSectionPart(const Shader& shader, const char* verticesPath, const char* indicesPath, glm::vec3 color, int mode)
	: shader(shader), vertices(verticesPath, indicesPath), trans(this->shader), color(color), mode(mode)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CraneHorizontalSectionPart::render(glm::mat4 view, float zoom, glm::vec3 light)
{
	glLineWidth(3);
	shader.use();
	shader.setVec3("color", color);
	shader.setVec3("light", light);
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	glPolygonMode(GL_FRONT_AND_BACK, mode);
	vertices.draw(true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

void CraneHorizontalSectionPart::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}