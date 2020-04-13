#include "Cylinder.h"

Cylinder::Cylinder(const char* vertexPath, const char* fragmentPath, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts)
:Primitive(vertexPath, fragmentPath), height(height), radius(radius), heightParts(heightParts), circleParts(circleParts)
{
	checkAndSetData();
}

Cylinder::Cylinder(const Shader& shader, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts)
	:Primitive(shader), height(height), radius(radius), heightParts(heightParts), circleParts(circleParts)
{
	checkAndSetData();
}

Cylinder::Cylinder(const Shader& shader, Texture* text, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts)
	: Primitive(shader, text), height(height), radius(radius), heightParts(heightParts), circleParts(circleParts)
{
	checkAndSetData();
}

void Cylinder::checkAndSetData()
{
	if (heightParts < 2) this->heightParts = 2;
	if (circleParts < 3) this->circleParts = 3;
}

Cylinder::~Cylinder()
{
	deleteInWordPrimary();
}

void Cylinder::deleteInWorld()
{
	deleteInWordPrimary();
}


void Cylinder::generateObject()
{
	generateObjectPrimitive();
}

/*
Vertices indexes example:
	7
  4 5 6
  1 2 3
	0
*/

GLfloat* Cylinder::generateVertices() const {
	GLfloat *vertices = new GLfloat[numberOfVerticesx3()];
	GLuint i = 0;


	for (GLuint repeat = 0; repeat < circleParts; ++repeat) {
		vertices[i] = 0.0;
		vertices[i + 1] = 0.0;
		vertices[i + 2] = 0.0;
		i += offset;
	}
	

	for (GLuint hParts = 0; hParts < heightParts; ++hParts) {
		setVerticesInCircle(vertices, hParts, i);
	}

	for (GLuint repeat = 0; repeat < circleParts; ++repeat) {
		vertices[i] = 0.0;
		vertices[i + 1] = 0.0;
		vertices[i + 2] = height;
		i += offset;
	}
	
	return vertices;
}

void Cylinder::setVerticesInCircle(GLfloat* vertices, const GLuint& hParts, GLuint& i) const
{
	GLuint itmp = i;

	for (GLuint circle = 0; circle < circleParts; ++circle, i += offset) {
		vertices[i] = radius * (GLfloat) sin(circle * 2 * M_PI / circleParts);
		vertices[i + 1] = radius * (GLfloat) cos(circle * 2 * M_PI / circleParts);
		vertices[i + 2] = hParts * height / (heightParts - 1);
	}

	vertices[i] = vertices[itmp];
	vertices[i + 1] = vertices[itmp + 1];
	vertices[i + 2] = vertices[itmp + 2];
	i += offset;
}

GLuint Cylinder::numberOfIndicesx3() const{
	GLuint upperBottomSum = circleParts * 2;
	GLuint wallsSum = (heightParts - 1) * circleParts * 2;

	return (upperBottomSum + wallsSum) * 3;
}

GLuint Cylinder::numberOfVerticesx3() const {
	if(isTexture) return ((circleParts + 1) * (heightParts) + 2 * circleParts) * 5;
	else return ((circleParts + 1) * (heightParts) + 2 * circleParts) * 3;
	/*if (isTexture) return ((circleParts + 1) * (heightParts + 2)) * 5;
	else return ((circleParts + 1) * (heightParts + 2)) * 3;*/
}

GLuint Cylinder::numberOfVertices() const {
	return ((circleParts + 1) * (heightParts) + 2 * circleParts) + 2;
	//return ((circleParts + 1) * (heightParts + 2));
}


GLuint* Cylinder::generateIndices() const {
	GLuint nextIndices = 3;

	GLuint numberOfIndices = numberOfIndicesx3();
	GLuint* indices = new GLuint[numberOfIndices];
	GLuint indicesPointer = 0;

	setIndicesToCenterBottom(indicesPointer, nextIndices, 0, getCircleIndexInVertices(0), indices, circleParts);

	// set walls
	for (GLuint hParts = 1; hParts < heightParts; ++hParts) {
		GLuint index1 = getCircleIndexInVertices(hParts - 1);
		GLuint index2 = getCircleIndexInVertices(hParts);

		// first triangle in rectangle
		setWallIndices(indicesPointer, nextIndices, indices, index1, index2, circleParts);
	}

	GLuint topIndex = getCircleIndexInVertices(heightParts - 1) + circleParts + 1;
	setIndicesToCenterBottom(indicesPointer, nextIndices, topIndex, getCircleIndexInVertices(heightParts - 1), indices, circleParts);
	//setIndicesToCenterTop(indicesPointer, nextIndices, topIndex, getCircleIndexInVertices(heightParts - 1), indices, circleParts);

	return indices;
}

GLuint Cylinder::getCircleIndexInVertices(const GLuint& circleNumber) const{
	return (circleNumber) * (circleParts + 1) + circleParts;
}

void Cylinder::render(glm::mat4 view, float zoom)
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

//void Cylinder::render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos)
//{
//	shader.use();
//
//	if (texture != nullptr) {
//		texture->prepareRenderTexture();
//		shader.setInt("Texture", 0);
//	}
//	shader.setVec3("ambient", ambient);
//	shader.setVec3("light", light);
//	shader.setVec3("lightPos", lightPos);
//	shader.setVec3("viewPos", cameraPos);
//
//	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
//	trans.setView(view);
//	trans.runAll();
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	draw(false);
//
//}

void Cylinder::draw(bool unbind)
{
	if (generated) {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, numberOfIndicesx3(), GL_UNSIGNED_INT, 0);
		if (unbind) glBindVertexArray(0);
	}
}

void Cylinder::generateTextCoord(GLfloat* vertices)
{
	GLuint index = textOffset;
	GLuint next = offset;
	GLfloat hStep = 1.0f / (heightParts + 1);
	GLfloat height = hStep;
	GLfloat wStep = 1.0f / (circleParts);
	GLfloat wStepBegin = 1.0f / (circleParts - 1);
	GLfloat width = 0;

	for (GLuint repeat = 0; repeat < circleParts; ++repeat, index += next, width += wStepBegin) {
		vertices[index] = width;
		vertices[index + 1] = 0;
	}
	width = 0;

	for (GLuint i = 0; i < heightParts; ++i, height += hStep) {
		for (GLuint j = 0; j <= circleParts; ++j, index += next, width += wStep) {
			vertices[index] = width;
			vertices[index + 1] = height;
		}
		width = 0;
	}

	for (GLuint repeat = 0; repeat < circleParts; ++repeat, index += next, width += wStepBegin) {
		vertices[index] = width;
		vertices[index + 1] = 1;
	}
}

void Cylinder::generateNormals(GLfloat* vertices)
{
	//GLuint i = normalOffset;
	//const GLuint step = offset;

	//TODO
}