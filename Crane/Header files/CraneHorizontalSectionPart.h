#pragma once

#define GLEW_STATIC // to mark that we use static library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"


class CraneHorizontalSectionPart
{
	Shader shader;
	VertexData3D vertices;
	glm::vec3 color;
	int mode;

public:
	Transform trans;
	CraneHorizontalSectionPart(const Shader& shader, const char* verticesPath, const char* indicesPath, glm::vec3 color, int mode=GL_FILL);

	void render(glm::mat4 view, float zoom, glm::vec3 light);
	void rotate(float angle);
};