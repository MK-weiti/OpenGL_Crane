#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"
#include "TextureContainer.h"

class Ground
{
	Shader shader;
	VertexData3D vertices;
	TextureContainer texContainer;
	Texture *groundtex;

public:
	Transform trans;

	Ground(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, Texture *Tex);
	~Ground();

	void render(glm::mat4 view, float zoom, glm::vec3 ambient, glm::vec3 light, glm::vec3 lightPos, glm::vec3 cameraPos);
};
