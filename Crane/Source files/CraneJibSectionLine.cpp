#include "CraneJibSectionLine.h"

CraneJibSectionLine::CraneJibSectionLine(const Shader& shader,  const char* verticesPath, const char* indicesPath, glm::vec4 color)
	:shader(shader), vertices(verticesPath, indicesPath), trans(this->shader), color(color)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CraneJibSectionLine::render(glm::mat4 view, float zoom, glm::vec3 light)
{
	shader.use();
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	shader.setVec3("color", color);
	shader.setVec3("light", light);
	trans.runAll();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CraneJibSectionLine::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}