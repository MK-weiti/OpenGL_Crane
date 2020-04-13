#pragma once

#include "Primitive.h"

Primitive::Primitive(const char* vertexPath, const char* fragmentPath)
	:shader(vertexPath, fragmentPath), EBO(0), VBO(0), VAO(0), generated(false), isColors(false), isTexture(false), trans(shader), \
	offset(3), textOffset(0), colorsOffset(0), texture(nullptr)
{}

Primitive::Primitive(const Shader& shader)
	:shader(shader), EBO(0), VBO(0), VAO(0), generated(false), isColors(false), isTexture(false), trans(this->shader), \
	offset(3), textOffset(0), colorsOffset(0), texture(nullptr)
{}

Primitive::Primitive(const Shader & shader, Texture* text)
	:shader(shader), EBO(0), VBO(0), VAO(0), generated(false), isColors(false), isTexture(false), trans(this->shader), \
	offset(3), textOffset(0), colorsOffset(0), texture(text)
{}

Primitive::~Primitive()
{}

void Primitive::deleteInWordPrimary()
{
	if (generated) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	generated = false;
}

void Primitive::setWallIndices(GLuint& indicesPointer, const GLuint& nextIndices, GLuint* indices, const GLuint& index1, const GLuint& index2, const GLuint& circleParts) const
{
	for (GLuint i = 1; i <= circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = index1 + i - 1;
		indices[indicesPointer + 1] = index1 + i;
		indices[indicesPointer + 2] = index2 + i - 1;
	}

	/*indices[indicesPointer] = index1 + circleParts - 1;
	indices[indicesPointer + 1] = index1;
	indices[indicesPointer + 2] = index2 + circleParts - 1;
	//indices[indicesPointer + 2] = index2;
	indicesPointer += nextIndices;*/

	// second triangle in rectangle
	for (GLuint i = 1; i <= circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = index2 + i - 1;
		indices[indicesPointer + 1] = index2 + i;
		indices[indicesPointer + 2] = index1 + i;
	}

	/*indices[indicesPointer] = index2 + circleParts - 1;
	indices[indicesPointer + 1] = index2;
	indices[indicesPointer + 2] = index1;
	//indices[indicesPointer + 2] = index1 - 1;
	indicesPointer += nextIndices;*/


	/*for (GLuint i = 1; i < circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = index1 + i - 1;
		indices[indicesPointer + 1] = index1 + i;
		indices[indicesPointer + 2] = index2 + i - 1;
	}

	indices[indicesPointer] = index1 + circleParts - 1;
	indices[indicesPointer + 1] = index1;
	indices[indicesPointer + 2] = index2 + circleParts - 1;
	//indices[indicesPointer + 2] = index2;
	indicesPointer += nextIndices;

	// second triangle in rectangle
	for (GLuint i = 1; i < circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = index2 + i - 1;
		indices[indicesPointer + 1] = index2 + i;
		indices[indicesPointer + 2] = index1 + i;
	}*/

	/*indices[indicesPointer] = index2 + circleParts - 1;
	indices[indicesPointer + 1] = index2;
	indices[indicesPointer + 2] = index1;
	//indices[indicesPointer + 2] = index1 - 1;
	indicesPointer += nextIndices;*/


}


/*
Warning
Because of wrapping texture around the first vertices in vertical position are copied.
*/
void Primitive::setIndicesToCenterBottom(GLuint& indicesPointer, const GLuint& nextIndices, const GLuint& centerIndex, const GLuint& startCircleIndex, GLuint* indices, const GLuint& circleParts) const
{
	/*for (GLuint i = 1; i <= circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = centerIndex + i - 1;
		indices[indicesPointer + 1] = startCircleIndex + i - 1;
		indices[indicesPointer + 2] = startCircleIndex + i;
	}*/

	/*for (GLuint i = 1; i < circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = centerIndex;
		indices[indicesPointer + 1] = startCircleIndex + i - 1;
		indices[indicesPointer + 2] = startCircleIndex + i;
	}

	indices[indicesPointer] = centerIndex;
	indices[indicesPointer + 1] = startCircleIndex;
	indices[indicesPointer + 2] = startCircleIndex + circleParts - 1;
	indicesPointer += nextIndices;*/

	for (GLuint i = 1; i < circleParts; ++i, indicesPointer += nextIndices) {
		indices[indicesPointer] = centerIndex;
		indices[indicesPointer + 1] = startCircleIndex + i - 1;
		indices[indicesPointer + 2] = startCircleIndex + i;
	}

	indices[indicesPointer] = centerIndex + 1;
	indices[indicesPointer + 1] = startCircleIndex + circleParts - 1;
	indices[indicesPointer + 2] = startCircleIndex + circleParts;
	indicesPointer += nextIndices;
}

void Primitive::setIndicesToCenterTop(GLuint& indicesPointer, const GLuint& nextIndices, const GLuint& centerIndex, const GLuint& startCircleIndex, GLuint* indices, const GLuint& circleParts) const
{
	/*for (GLuint i = circleParts; i >= 1; --i, indicesPointer += nextIndices) {
		indices[indicesPointer] = centerIndex + i - 1;
		indices[indicesPointer + 1] = startCircleIndex + i - 1;
		indices[indicesPointer + 2] = startCircleIndex + i;
	}*/

	for (GLuint i = circleParts; i >= 1; --i, indicesPointer += nextIndices) {
		indices[indicesPointer] = centerIndex;
		indices[indicesPointer + 1] = startCircleIndex + i - 1;
		indices[indicesPointer + 2] = startCircleIndex + i;
	}
}

void Primitive::generateObjectPrimitive()
{
	setOffset();
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	GLfloat* vertices = generateVertices();
	GLuint* indices = generateIndices();
	if (isTexture) generateTextCoord(vertices);
	if (isNormal) generateNormals(vertices);


#ifdef _DEBUG
	GLuint sumControl = 0;
	std::cout << "Offset: " << offset << " textOffset: " << textOffset << " colorsOffset: " << colorsOffset << "\n";
	std::cout << "Indices: " << numberOfIndicesx3() << "\n";
	for (GLuint i = 0; i < numberOfIndicesx3(); i += 3) {
		std::cout << i / 3 << ": " << indices[i] << " " << indices[i + 1] << " " << indices[i + 2] << "\n";
		++sumControl;
		//if (sumControl > 0xFF) throw std::runtime_error("infinite loop");
	}

	sumControl = 0;

	std::cout << "Vertices: " << numberOfVerticesx3() << "\n";
	for (GLuint i = 0; i < numberOfVerticesx3(); i += offset) {
		std::cout << i / offset << ": ";
		for (GLuint j = 0; j < offset; ++j) {
			std::cout << vertices[i + j] << " ";
			++sumControl;
			//if (sumControl > 0xFF * offset) throw std::runtime_error("infinite loop");
		}
		std::cout << "\n";
	}
#endif

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numberOfIndicesx3(), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// idk why but when there is not +1 then there is ugly stripe
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (numberOfVerticesx3() + 1), vertices, GL_STATIC_DRAW);

	GLuint indexAttr = 0;

	glVertexAttribPointer(indexAttr, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(indexAttr);
	++indexAttr;

	if (isTexture) {
		glVertexAttribPointer(indexAttr, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), (GLvoid*)(textOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(indexAttr);
		++indexAttr;
	}

	if (isNormal) {
		glVertexAttribPointer(indexAttr, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), (GLvoid*)(normalOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(indexAttr);
		++indexAttr;
	}

	if (isColors) {
		glVertexAttribPointer(indexAttr, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), (GLvoid*)(colorsOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(indexAttr);
		++indexAttr;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	generated = true;
	delete[] vertices;
	delete[] indices;
}

void Primitive::setOffset()
{
	if (isNormal) {
		if (isTexture) {
			if (isColors) {
				offset = 11;
				colorsOffset = 3;
				textOffset = 6;
				normalOffset = 8;
			}
			else {
				offset = 8;
				colorsOffset = 0;
				textOffset = 3;
				normalOffset = 5;
			}
		}
		else {
			if (isColors) {
				offset = 9;
				colorsOffset = 3;
				textOffset = 0;
				normalOffset = 6;
			}
			else {
				offset = 6;
				colorsOffset = 0;
				textOffset = 0;
				normalOffset = 3;
			}
		}
	}
	else {
		normalOffset = 0;

		if (isTexture) {
			if (isColors) {
				offset = 8;
				colorsOffset = 3;
				textOffset = 6;
			}
			else {
				offset = 5;
				colorsOffset = 0;
				textOffset = 3;
			}
		}
		else {
			if (isColors) {
				offset = 6;
				colorsOffset = 3;
				textOffset = 0;
			}
			else {
				offset = 3;
				colorsOffset = 0;
				textOffset = 0;
			}
		}
	}
	
}

void Primitive::setTextGen(bool condition)
{
	if(!generated) isTexture = condition;
}

void Primitive::setColorsGen(bool condition)
{
	if(!generated) isColors = condition;
}

void Primitive::setNormalGen(bool condition)
{
	if (!generated) isNormal = condition;
}


GLuint Primitive::numberOfVerticesx3Primitive(const GLuint& sum) const{
	if (isNormal) {
		if (isTexture) {
			if(isColors) return sum * 11;
			else return sum * 8;
		}
		else {
			if (isColors) return sum * 8;
			else return sum * 6;
		}
	}
	else if (isTexture) {
		if (isColors) return sum * 8;
		else return sum * 5;
	}
	else {
		return sum * 3;
	}
}