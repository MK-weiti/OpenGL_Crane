#include "Ground.h"

Ground::Ground(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture *Tex)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath, false, 6), trans(shader), groundtex(Tex)
{
	trans.translate(0.0f, -3.7f, -10.0f);
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	vertices.onlyVertexData = false;
	vertices.prepareToSetVertexData(2);
	vertices.componentsPerVertexAttribute[0] = vertices.componentsPerVertexAttribute[1] = 3;
	vertices.dataTypes[0] = vertices.dataTypes[1] = GL_FLOAT;
	vertices.ifNormalized[0] = vertices.ifNormalized[1] = GL_FALSE;
	vertices.offset = 6 * sizeof(GLfloat);
	vertices.componentOffset[0] = 0;
	vertices.componentOffset[1] = 3 * sizeof(GLfloat);
	vertices.generateAndSet();
}

Ground::~Ground() {}

void Ground::render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos)
{
	shader.use();

	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();

	groundtex->prepareRenderTexture();

	shader.setVec3("ambient", ambient);
	shader.setVec3("light", light);
	shader.setVec3("lightPos", lightPos);
	shader.setVec3("viewPos", cameraPos);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	vertices.draw(true);
}