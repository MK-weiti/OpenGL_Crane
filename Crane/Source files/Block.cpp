#include "Block.h"

Block::Block(const Shader& shader, Texture* textureSide, Texture* textureTop, const char* verticesPath, const char* indicesPath)
	: shader(shader), textureSide(textureSide), textureTop(textureTop), vertices(verticesPath, indicesPath, false, 5), trans(this->shader) {
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

void Block::render(glm::mat4 view, float zoom)
{
	shader.use();

	if (textureSide != nullptr) {
		textureSide->prepareRenderTexture();
		//shader.setInt("Texture", 0);
	}
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	vertices.drawPart(0);
	vertices.drawPart(1);
	vertices.drawPart(4);
	vertices.drawPart(5);
	if (textureTop != nullptr) {
		textureTop->prepareRenderTexture();
		shader.setInt("Texture", 0);
	}
	vertices.drawPart(2);
	vertices.drawPart(3);
	vertices.drawPart(6);
	vertices.drawPart(7);
	vertices.drawPart(9);
	vertices.drawPart(10);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}