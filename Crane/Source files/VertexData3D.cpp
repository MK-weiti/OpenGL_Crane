#include "VertexData3D.h"

VertexData3D::VertexData3D(const char* vertexPath, const char* fragmentPath, const bool generate, const int numberOfAttributes)
{
	std::string vertexCode;
	std::string indicesCode;
	std::ifstream vShaderFile;
	std::ifstream iShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	iShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		iShaderFile.open(fragmentPath);
		std::stringstream vStream, iStream;
		// read file's buffer contents into streams
		vStream << vShaderFile.rdbuf();
		iStream << iShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		iShaderFile.close();

		vStream >> numberOfVertices;
		iStream >> numberOfIndices;
		repetitiveStructFloats = numberOfVertices * numberOfAttributes;
		repetitiveStructIntegers = numberOfIndices * 3;

		vertices = new GLfloat[repetitiveStructFloats];
		indices = new GLuint[repetitiveStructIntegers];

#ifdef _DEBUG
		unsigned int v3 = 0, i3 = 0;
		std::cout << "Vertices (" << vertexPath << "):" << std::endl;
#endif

		for (GLuint i = 0; i < repetitiveStructFloats; ++i) {
			vStream >> vertices[i];


#ifdef _DEBUG
			std::cout << vertices[i] << " ";
			if (++v3 % 3 == 0) std::cout << std::endl;
#endif


		}

#ifdef _DEBUG
		std::cout << "Indices (" << fragmentPath << "):" << std::endl;
#endif

		for (GLuint i = 0; i < repetitiveStructIntegers; ++i) {
			iStream >> indices[i];


#ifdef _DEBUG
			std::cout << indices[i] << " ";
			if (++i3 % 3 == 0) std::cout << std::endl;
#endif


		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::VERTICES::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	if(generate) generateAndSet();
}

void VertexData3D::generateAndSet()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * repetitiveStructFloats, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * repetitiveStructIntegers, indices, GL_STATIC_DRAW);

	if (onlyVertexData) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	else {
		for (GLuint i = 0; i < numberOfVertexAttribute; ++i) {
			glVertexAttribPointer(i, componentsPerVertexAttribute[i], dataTypes[i], ifNormalized[i], offset, (GLvoid*)componentOffset[i]);
			glEnableVertexAttribArray(i);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
}

VertexData3D::~VertexData3D()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	delete componentsPerVertexAttribute;
	delete dataTypes;
	delete ifNormalized;
	delete componentOffset;
}

void VertexData3D::draw(bool unbind)
{	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, repetitiveStructIntegers, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	if(unbind) glBindVertexArray(0);
}

void VertexData3D::drawPart(GLint first, GLsizei count, bool unbind)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, first, count);
	if (unbind) glBindVertexArray(0);
}

void VertexData3D::prepareToSetVertexData(GLuint numberOfVertexAttribute)
{
	this->numberOfVertexAttribute = numberOfVertexAttribute;
	componentsPerVertexAttribute = new GLint[numberOfVertexAttribute];
	dataTypes = new GLenum[numberOfVertexAttribute];
	ifNormalized = new GLboolean[numberOfVertexAttribute];
	componentOffset = new GLuint[numberOfVertexAttribute];
}