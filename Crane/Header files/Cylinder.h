#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <VertexData3D.h>
#include <Primitive.h>

/*
Cylinder has its point in centre at bottom
*/

class Cylinder: public Primitive
{
	GLfloat height;
	GLfloat radius;
	GLuint heightParts;
	GLuint circleParts;

	void setVerticesInCircle(GLfloat* vertices, const GLuint& hParts, GLuint& i) const;
	GLuint getCircleIndexInVertices(const GLuint& circleNumber) const;

	GLfloat* generateVertices() const;	// return generated vertices
	GLuint* generateIndices() const;	// return generated indices

	GLuint numberOfIndicesx3() const;
	GLuint numberOfVerticesx3() const;
	GLuint numberOfVertices() const;

	void generateTextCoord(GLfloat* vertices);
	void generateNormals(GLfloat* vertices);

public:

	// height parts should be 2, there is no reason to give it more
	Cylinder(const char* vertexPath, const char* fragmentPath, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts);
	Cylinder(const Shader& shader, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts);
	Cylinder(const Shader& shader, Texture* text, const GLfloat& height, const GLfloat& radius, const GLuint& heightParts, const GLuint& circleParts);
	void checkAndSetData();
	~Cylinder();

	void deleteInWorld();	// delete from graphics card but data object class still exist
	void generateObject();
	void draw(bool unbind);	// without matrix
	void render(glm::mat4 view, float zoom);	// with matrix
	//void render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos);
	
};
