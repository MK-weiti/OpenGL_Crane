#include "CraneJibSectionPart.h"

CraneJibSectionPart::CraneJibSectionPart(const Shader& shader, Texture* texture, const char* verticesPath, const char* indicesPath)
	:shader(shader), texture(texture), vertices(verticesPath, indicesPath,false,5), trans(this->shader)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	vertices.onlyVertexData = false;
	vertices.prepareToSetVertexData(2);
	vertices.componentsPerVertexAttribute[0] = 3;
	vertices.componentsPerVertexAttribute[1] = 2;
	vertices.dataTypes[0] = GL_FLOAT;
	vertices.dataTypes[1] = GL_FLOAT;
	vertices.ifNormalized[0] = GL_FALSE;
	vertices.ifNormalized[1] = GL_FALSE;
	vertices.offset = 5 * sizeof(GLfloat);
	vertices.componentOffset[0] = 0;
	vertices.componentOffset[1] = 3 * sizeof(GLfloat);
	vertices.generateAndSet();
}

void CraneJibSectionPart::render(glm::mat4 view, float zoom, glm::vec3 light)
{
	shader.use();
	if (texture != nullptr) {
		texture->prepareRenderTexture();
		shader.setInt("Texture", 0);
	}

	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	//shader.setVec3("color", color);
	shader.setVec3("light", light);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void CraneJibSectionPart::rotate(float angle, float x, float y, float z)
{
	trans.rotateAndRun(glm::radians(angle), x, y, z);
}