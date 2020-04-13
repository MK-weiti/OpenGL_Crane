#include "Cuboid.h"

Cuboid::Cuboid(const char* vertexPath, const char* fragmentPath, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree)
	:Primitive(vertexPath, fragmentPath), sizeOne(sizeOne), sizeTwo(sizeTwo), sizeThree(sizeThree)
{}


Cuboid::Cuboid(const Shader& shader, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree)
	: Primitive(shader), sizeOne(sizeOne), sizeTwo(sizeTwo), sizeThree(sizeThree)
{}

Cuboid::Cuboid(const Shader& shader, Texture* text, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree)
	: Primitive(shader, text), sizeOne(sizeOne), sizeTwo(sizeTwo), sizeThree(sizeThree)
{}


Cuboid::~Cuboid() {
	deleteInWordPrimary();
}

void Cuboid::deleteInWorld()
{
	deleteInWordPrimary();
}

GLfloat* Cuboid::generateVertices() const
{
	GLfloat hOne = sizeOne / 2, hTwo = sizeTwo / 2, hThree = sizeThree / 2;
	GLfloat* vertices = new GLfloat[numberOfVerticesx3()];
	const GLuint step = offset;

	GLuint i = 0;

	// set bottom and top
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = hOne;
		vertices[i + 1] = -hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = -hOne;
		vertices[i + 1] = -hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = -hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = hThree;
		i += step;

		hThree = -hThree;
	}

	// set 2 walls
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = -hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = -hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = -hThree;
		i += step;

		vertices[i] = hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = -hThree;
		i += step;

		hTwo = -hTwo;
	}
	
	// set 2 walls
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = hOne;
		vertices[i + 1] = -hTwo;
		vertices[i + 2] = hThree;
		i += step;

		vertices[i] = hOne;
		vertices[i + 1] = -hTwo;
		vertices[i + 2] = -hThree;
		i += step;

		vertices[i] = hOne;
		vertices[i + 1] = hTwo;
		vertices[i + 2] = -hThree;
		i += step;

		hOne = -hOne;
	}
	
	return vertices;
}

GLuint* Cuboid::generateIndices() const
{
	GLuint* indices = new GLuint[numberOfIndicesx3()];
	GLuint index = 0;
	GLuint step = 3;
	
	for (GLuint i = 0; i < 6; ++i) {
		indices[index] = i * 4;
		indices[index + 1] = i * 4 + 1;
		indices[index + 2] = i * 4 + 2;
		index += step;

		indices[index] = i * 4;
		indices[index + 1] = i * 4 + 2;
		indices[index + 2] = i * 4 + 3;
		index += step;
	}

	return indices;
}

void Cuboid::generateTextCoord(GLfloat* vertices) {
	if (isTexture == false) return;

	GLuint index = textOffset;
	
	for (GLuint i = 0; i < 6; ++i) {
		vertices[index] = 0.0f;
		vertices[index + 1] = 0.0f;
		index += offset;

		vertices[index] = 1.0f;
		vertices[index + 1] = 0.0f;
		index += offset;

		vertices[index] = 1.0f;
		vertices[index + 1] = 1.0f;
		index += offset;

		vertices[index] = 0.0f;
		vertices[index + 1] = 1.0f;
		index += offset;
	}
}

void Cuboid::generateNormals(GLfloat* vertices) {
	GLfloat x = 1.0f, y = 1.0f, z = 1.0f;
	GLuint i = normalOffset;
	const GLuint step = offset;
	
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = 0.0f;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = z;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = z;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = z;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = z;
		i += step;

		z = -z;
	}

	// set 2 walls
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = 0.0f;
		vertices[i + 1] = y;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = y;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = y;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = 0.0f;
		vertices[i + 1] = y;
		vertices[i + 2] = 0.0f;
		i += step;

		y = -y;
	}

	// set 2 walls
	for (GLuint k = 0; k < 2; ++k) {
		vertices[i] = x;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = x;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = x;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = 0.0f;
		i += step;

		vertices[i] = x;
		vertices[i + 1] = 0.0f;
		vertices[i + 2] = 0.0f;
		i += step;

		x = -x;
	}

}

void Cuboid::generateObject()
{
	generateObjectPrimitive();
}

GLuint Cuboid::numberOfIndicesx3() const
{
	return 6 * 2 * 3;
}

GLuint Cuboid::numberOfVerticesx3() const
{
	GLuint sum = 6 * 4;
	
	return numberOfVerticesx3Primitive(sum);
}

void Cuboid::draw(bool unbind)
{
	if (generated) {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, numberOfIndicesx3(), GL_UNSIGNED_INT, 0);
		if (unbind) glBindVertexArray(0);
	}
}

void Cuboid::render(glm::mat4 view, float zoom)
{
	shader.use();

	if (texture != nullptr) {
		texture->prepareRenderTexture();
		shader.setInt("Texture", 0);
	}

	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	draw(false);
}

void Cuboid::render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos)
{
	shader.use();

	if (texture != nullptr) {
		texture->prepareRenderTexture();
		shader.setInt("Texture", 0);
	}
	shader.setVec3("ambient", ambient);
	shader.setVec3("light", light);
	shader.setVec3("lightPos", lightPos);
	shader.setVec3("viewPos", cameraPos);

	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	draw(false);
}
