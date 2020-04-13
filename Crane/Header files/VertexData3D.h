#pragma once

#define GLEW_STATIC // to mark that we use static library

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VertexData3D
{
private:
	GLuint EBO = 0;	// gives instruction which vertices should create triangle
	GLuint VBO = 0;	// stores large number of data (example: vertices)
	GLuint VAO = 0;

public:	// this is data if in vertices you will want to add other information, for example texture

	GLboolean onlyVertexData = true;	// false if data below is set
	GLuint numberOfVertexAttribute = 1;	// how many different types of data is stored in vertices
	GLint *componentsPerVertexAttribute = nullptr;
	GLenum *dataTypes = nullptr;
	GLboolean *ifNormalized = nullptr;
	GLsizei offset;	// in bytes between vertices ((6*sizeof(GLfloat))
	GLuint *componentOffset = nullptr;	// in bytes between attributes in vertices (0, 3*sizeof(GLfloat), later in method it is cast to (void*)

private:
	GLfloat *vertices;
	GLuint numberOfVertices;	// number of vertices per vertex attribute
	GLuint repetitiveStructFloats;	// it is number of floats in repetitive structure in VBO

	GLuint *indices;
	GLuint numberOfIndices;		// number of indices per vertex attribute
	GLuint repetitiveStructIntegers; // it is number of integers in repetitive structure in EBO

public:
	VertexData3D(const char* vertexPath, const char* fragmentPath, const bool generate = true, int numberOfAttributes=3);
	void prepareToSetVertexData(GLuint numberOfVertexAttribute);	// only allocate memory, remember to set data later
	void generateAndSet();	// you should use this only once
	~VertexData3D();

	void draw(bool unbind = true);
	void drawPart(GLint first, GLsizei count=3, bool unbind = true);
};

