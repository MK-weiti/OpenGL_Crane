#pragma once
#include <Primitive.h>

class Cuboid: public Primitive
{
	GLfloat sizeOne;
	GLfloat sizeTwo;
	GLfloat sizeThree;

	GLfloat* generateVertices() const;	// return generated vertices
	GLuint* generateIndices() const;	// return generated indices
	void generateTextCoord(GLfloat* vertices);
	void generateNormals(GLfloat* vertices);

	GLuint numberOfIndicesx3() const;
	GLuint numberOfVerticesx3() const;

public:

	Cuboid(const char* vertexPath, const char* fragmentPath, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree);
	Cuboid(const Shader& shader, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree);
	Cuboid(const Shader& shader, Texture* text, const GLfloat& sizeOne, const GLfloat& sizeTwo, const GLfloat& sizeThree);
	~Cuboid();

	void deleteInWorld();
	void generateObject();
	void draw(bool unbind);	// without matrix
	void render(glm::mat4 view, float zoom);// with matrix
	void render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos);
};	


