#pragma once
#include <Primitive.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Ellipsoid: public Primitive
{
	GLuint verticalParts;
	GLuint polygonParts;
	GLfloat radiusX;
	GLfloat radiusY;
	GLfloat radiusZ;

	GLfloat* generateVertices() const;
	GLuint* generateIndices() const;

	GLuint numberOfIndicesx3() const;
	GLuint numberOfVertices() const;
	GLuint numberOfVerticesx3() const;
	GLuint numberOfIndices() const;

	void checkAndSetData();
	GLuint getCircleIndexInVertices(const GLuint& heightPart) const;

	GLfloat parametricX(const GLdouble& longitude, const GLdouble& latitude) const;
	GLfloat parametricY(const GLdouble& longitude, const GLdouble& latitude) const;
	GLfloat parametricZ(const GLdouble& longitude, const GLdouble& latitude) const;

	void generateTextCoord(GLfloat* vertices);
	void generateNormals(GLfloat* vertices);

public:
	Ellipsoid(const char* vertexPath, const char* fragmentPath, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts);
	Ellipsoid(const Shader& shader, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts);
	Ellipsoid(const Shader& shader, Texture* text, const GLfloat& radius, const GLuint& verticalParts, const GLuint& polygonParts);

	Ellipsoid(const char* vertexPath, const char* fragmentPath, const GLfloat& radiusX, const GLfloat& radiusY, \
		const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts);
	Ellipsoid(const Shader& shader, const GLfloat& radiusX, const GLfloat& radiusY, \
		const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts);
	Ellipsoid(const Shader& shader, Texture* text, const GLfloat& radiusX, const GLfloat& radiusY, \
		const GLfloat& radiusZ, const GLuint& verticalParts, const GLuint& polygonParts);

	~Ellipsoid();

	void deleteInWorld();
	void generateObject();
	void draw(bool unbind);
	void render(glm::mat4 view, float zoom);
};

