#pragma once
#include <Shader.h>
#include <Transform.h>
#include <TextureContainer.h>

class Primitive
{
protected:
	Shader shader;

	GLuint EBO;
	GLuint VBO;
	GLuint VAO;

	bool generated;
	bool isColors;
	bool isTexture;
	bool isNormal;

	GLuint offset;
	GLuint colorsOffset;
	GLuint textOffset;
	GLuint normalOffset;

	Texture* texture;

	void deleteInWordPrimary();
	void setWallIndices(GLuint& indicesPointer, const GLuint& nextIndices, GLuint* indices, const GLuint& index1, const GLuint& index2, const GLuint& circleParts) const;
	void setIndicesToCenterBottom(GLuint& indicesPointer, const GLuint& nextIndices, const GLuint& centerIndex, const GLuint& startCircleIndex, GLuint* indices, const GLuint& circleParts) const;
	void setIndicesToCenterTop(GLuint& indicesPointer, const GLuint& nextIndices, const GLuint& centerIndex, const GLuint& startCircleIndex, GLuint* indices, const GLuint& circleParts) const;

	void generateObjectPrimitive();

	void setOffset();

	virtual GLfloat* generateVertices() const = 0;
	virtual GLuint* generateIndices() const = 0;

	virtual GLuint numberOfIndicesx3() const = 0;
	virtual GLuint numberOfVerticesx3() const = 0;

	virtual void generateTextCoord(GLfloat* vertices) = 0;
	virtual void generateNormals(GLfloat* vertices) = 0;

	GLuint numberOfVerticesx3Primitive(const GLuint& sum) const;

public:
	Transform trans;

	Primitive(const char* vertexPath, const char* fragmentPath);
	Primitive(const Shader& shader);
	Primitive(const Shader& shader, Texture* text);
	~Primitive();

	virtual void deleteInWorld() = 0;	// delete from graphics card but data object class still exist
	virtual void generateObject() = 0;
	virtual void draw(bool unbind) = 0;	// without matrix
	virtual void render(glm::mat4 view, float zoom) = 0;

	void setTextGen(bool condition);
	void setColorsGen(bool condition);
	void setNormalGen(bool condition);
};

