#pragma once

#define GLEW_STATIC // to mark that we use static library
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"
#include "Cylinder.h"
#include "ShaderContainer.h"


class CraneVerticalSectionPart
{
	Shader shader;
	VertexData3D vertices;
	GLuint shaderID;
	Cylinder cylinder;
	//Cylinder cylinders[8];
	//ShaderContainer* shaderContainer;
public:
	Transform trans, transTilt;

	CraneVerticalSectionPart(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture* beamText);
	//CraneVerticalSectionPart(const char* vertexPath, const char* fragmentPath);
	CraneVerticalSectionPart(const Shader& shader, const char* verticesPath, const char* indicesPath, Texture* beamText);
	~CraneVerticalSectionPart();

	void render(glm::mat4 view, float zoom);
};

