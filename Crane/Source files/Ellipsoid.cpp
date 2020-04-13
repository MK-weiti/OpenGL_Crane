#include "Ellipsoid.h"

Ellipsoid::Ellipsoid(const char* vertexPath, const char* fragmentPath, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts)
	:Primitive(vertexPath, fragmentPath), radiusX(radius), radiusY(radius), radiusZ(radius), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

Ellipsoid::Ellipsoid(const Shader& shader, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts)
	:Primitive(shader), radiusX(radius), radiusY(radius), radiusZ(radius), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

Ellipsoid::Ellipsoid(const char* vertexPath, const char* fragmentPath, const GLfloat& radiusX, const GLfloat& radiusY, const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts)
	: Primitive(vertexPath, fragmentPath), radiusX(radiusX), radiusY(radiusY), radiusZ(radiusZ), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

Ellipsoid::Ellipsoid(const Shader& shader, const GLfloat& radiusX, const GLfloat& radiusY, const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts)
	: Primitive(shader), radiusX(radiusX), radiusY(radiusY), radiusZ(radiusZ), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

Ellipsoid::Ellipsoid(const Shader& shader, Texture* text, const GLfloat& radiusX, const GLfloat& radiusY, const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts)
	: Primitive(shader, text), radiusX(radiusX), radiusY(radiusY), radiusZ(radiusZ), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

Ellipsoid::Ellipsoid(const Shader& shader, Texture* text, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts)
	: Primitive(shader, text), radiusX(radius), radiusY(radius), radiusZ(radius), verticalParts(verticalParts), polygonParts(polygonParts)
{
	checkAndSetData();
}

void Ellipsoid::checkAndSetData() {
	if (polygonParts < 3) this->polygonParts = 3;
	if (verticalParts < 1) this->verticalParts = 1;
	if (radiusX <= 0) this->radiusX = 1.0f;
	if (radiusY <= 0) this->radiusY = 1.0f;
	if (radiusZ <= 0) this->radiusZ = 1.0f;
}

Ellipsoid::~Ellipsoid()
{
	deleteInWordPrimary();
}

void Ellipsoid::deleteInWorld()
{
	deleteInWordPrimary();
}

void Ellipsoid::generateObject()
{
	generateObjectPrimitive();
}

void Ellipsoid::draw(bool unbind)
{
	if (generated) {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, numberOfIndicesx3(), GL_UNSIGNED_INT, 0);
		if (unbind) glBindVertexArray(0);
	}
}

void Ellipsoid::render(glm::mat4 view, float zoom)
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

GLfloat* Ellipsoid::generateVertices() const
{
	/*
	Using parametric equation
	longitude -> [-pi, pi) (horizontal)
	latitude -> [-pi/2, pi/2] (vertical)
	*/

	GLfloat* ret = new GLfloat[numberOfVerticesx3()];
	GLuint index = 0;

	GLdouble verticalStep = M_PI / (verticalParts + 1);
	GLdouble verticalBegin = (-M_PI / 2) + verticalStep;

	GLdouble horizontalStep = 2 * M_PI / (polygonParts);
	GLdouble horizontalBegin = -M_PI;

	GLdouble horizontalBeginTmp = horizontalBegin;

	/*for (GLuint i = 0; i < polygonParts; ++i) {
		ret[index] = 0;
		ret[index + 1] = -radiusY;
		ret[index + 2] = 0;
		index += offset;
	}*/
	
	ret[index] = 0;
	ret[index + 1] = -radiusY;
	ret[index + 2] = 0;
	index += offset;

	ret[index] = 0;
	ret[index + 1] = -radiusY;
	ret[index + 2] = 0;
	index += offset;
	
	for (GLuint i = 0; i < verticalParts; ++i, verticalBegin += verticalStep) {		
		GLuint indextmp = index;

		for (GLuint j = 0; j < polygonParts; ++j, horizontalBeginTmp += horizontalStep) {
			
			ret[index] = parametricX(horizontalBeginTmp, verticalBegin);
			ret[index + 1] = parametricY(horizontalBeginTmp, verticalBegin);
			ret[index + 2] = parametricZ(horizontalBeginTmp, verticalBegin);
			index += offset;
		}
		horizontalBeginTmp = horizontalBegin;

		ret[index] = ret[indextmp];
		ret[index + 1] = ret[indextmp + 1];
		ret[index + 2] = ret[indextmp + 2];
		index += offset;
	}
	
	/*for (GLuint i = 0; i < polygonParts; ++i) {
		ret[index] = 0;
		ret[index + 1] = radiusY;
		ret[index + 2] = 0;
		index += offset;
	}*/

	ret[index] = 0;
	ret[index + 1] = radiusY;
	ret[index + 2] = 0;
	index += offset;

	ret[index] = 0;
	ret[index + 1] = radiusY;
	ret[index + 2] = 0;
	index += offset;

	return ret;
}

GLuint* Ellipsoid::generateIndices() const
{
	GLuint* ret = new GLuint[numberOfIndicesx3()];
	GLuint index = 0;
	GLuint topCircleIndicesStart = getCircleIndexInVertices(verticalParts - 1);

	setIndicesToCenterBottom(index, 3, 0, getCircleIndexInVertices(0), ret, polygonParts);

	for (GLuint i = 1; i < verticalParts; ++i) {
		GLuint index1 = getCircleIndexInVertices(i - 1);
		GLuint index2 = getCircleIndexInVertices(i);

		setWallIndices(index, 3, ret, index1, index2, polygonParts);
	}
	//setIndicesToCenterTop(index, 3, getCircleIndexInVertices(verticalParts - 1) + polygonParts + 1, topCircleIndicesStart, ret, polygonParts);
	//setIndicesToCenterBottom(index, 3, getCircleIndexInVertices(verticalParts - 1) + polygonParts + 1, topCircleIndicesStart, ret, polygonParts);
	setIndicesToCenterBottom(index, 3, getCircleIndexInVertices(verticalParts - 1) + polygonParts + 1, topCircleIndicesStart, ret, polygonParts);

	return ret;
}

GLuint Ellipsoid::getCircleIndexInVertices(const GLuint& heightPart) const{
	//return (polygonParts + 1) * heightPart + polygonParts;
	//return (polygonParts) * heightPart + 1;
	return (polygonParts + 1) * heightPart + 2;
}

GLfloat Ellipsoid::parametricX(const GLdouble& longitude, const GLdouble& latitude) const {
	return GLfloat (radiusX * cos(longitude) * cos(latitude));
}

GLfloat Ellipsoid::parametricY(const GLdouble& longitude, const GLdouble& latitude) const {
	return GLfloat (radiusY * sin(latitude));
}

GLfloat Ellipsoid::parametricZ(const GLdouble& longitude, const GLdouble& latitude) const {
	return GLfloat (radiusZ * sin(longitude) * cos(latitude));
}

GLuint Ellipsoid::numberOfVerticesx3() const
{
	/*if(isTexture) return (verticalParts * (polygonParts + 1) + 2 * polygonParts) * 5;
	else return (verticalParts * (polygonParts + 1) + 2 * polygonParts) * 3;*/
	/*if (isTexture) return (verticalParts * (polygonParts) + 2) * 5;
	else return (verticalParts * (polygonParts) + 2) * 3;*/
	if (isTexture) return (verticalParts * (polygonParts + 1)+4) * 5;
	else return (verticalParts * (polygonParts + 1)+4) * 3;
}

GLuint Ellipsoid::numberOfVertices() const
{
	//return (verticalParts * (polygonParts + 1) + 2 * polygonParts);
	//return (verticalParts * (polygonParts) + 2);
	return (verticalParts * (polygonParts + 1)+4);
}

GLuint Ellipsoid::numberOfIndicesx3() const
{
	return polygonParts * verticalParts * 6;
}

GLuint Ellipsoid::numberOfIndices() const
{
	return polygonParts * (verticalParts + 1);
}

void Ellipsoid::generateTextCoord(GLfloat* vertices)
{
	GLuint index = textOffset;
	GLuint next = offset;
	GLfloat hStep = 1.0f / (verticalParts + 1);
	GLfloat height = hStep;
	GLfloat wStep = 1.0f / (polygonParts);
	GLfloat wStepBegin = 1.0f / (polygonParts - 1);
	GLfloat width = 0;


	/*for (GLuint i = 0; i < polygonParts; ++i, width += wStepBegin, index += next) {
		vertices[index] = width;
		vertices[index + 1] = 0;
	}
	width = 0;

	for (GLuint i = 0; i < verticalParts; ++i, height += hStep) {
		for (GLuint j = 0; j <= polygonParts; ++j, index += next, width += wStep) {
			std::cout << "VER: " << width << " :: " << height << std::endl;
			vertices[index] = width;
			vertices[index + 1] = height;

		}
		width = 0;
	}

	for (GLuint i = 0; i < polygonParts; ++i, width += wStep, index += next) {
		vertices[index] = width;
		vertices[index + 1] = 1;
	}*/

	GLuint indexVec = 0;
	GLuint indexTex = textOffset;
	GLuint i = 0;

	/*for (; i < polygonParts; ++i, indexVec += next, indexTex += next) {
		vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI);
		vertices[indexTex + 1] = 1.0f;
	}*/

	/*for (; i < numberOfVertices(); ++i, indexVec += next, indexTex += next) {
		vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / ( 2 * M_PI);
		vertices[indexTex + 1] = 0.5f - asin(vertices[indexVec + 1]) / M_PI;
	}*/

	/*for (; i < numberOfVertices(); ++i, indexVec += next, indexTex += next) {
		vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI);
		vertices[indexTex + 1] = 0.0f;
	}*/

	/*vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI);
	vertices[indexTex + 1] = 0.5f - asin(vertices[indexVec + 1]) / M_PI;
	++i;
	indexVec += next;
	indexTex += next;

	for (; i < polygonParts; ++i, indexVec += next, indexTex += next) {
		vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI);
		vertices[indexTex + 1] = 0.5f - asin(vertices[indexVec + 1]) / M_PI;
	}

	vertices[indexTex] = 0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI);
	vertices[indexTex + 1] = 0.0f;
	++i;
	indexVec += next;
	indexTex += next;*/

	

	for (; i < numberOfVertices(); ++i, indexVec += next, indexTex += next) {
		if (i == 1) {
			vertices[indexTex] = 0.5f;
			vertices[indexTex + 1] = (GLfloat) (0.5f - asin(vertices[indexVec + 1]) / M_PI);
		}
		if (i == numberOfVertices() - 1) {
			vertices[indexTex] = 0.5f;
			vertices[indexTex + 1] = (GLfloat)(0.5f - asin(vertices[indexVec + 1]) / M_PI);
		}

		if (i != 0 && i != 1 && i % (polygonParts + 1) == 1) {
			vertices[indexTex] = 1.0f;
			vertices[indexTex + 1] = (GLfloat)(0.5f - asin(vertices[indexVec + 1]) / M_PI);
			continue;
		}

		vertices[indexTex] = (GLfloat)(0.5f + atan2(vertices[indexVec + 2], vertices[indexVec]) / (2 * M_PI));
		vertices[indexTex + 1] = (GLfloat)(0.5f - asin(vertices[indexVec + 1]) / M_PI);
		
	}



}

void Ellipsoid::generateNormals(GLfloat* vertices)
{
	// TODO
}