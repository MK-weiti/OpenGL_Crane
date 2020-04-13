#pragma once

#define GLEW_STATIC // to mark that we use static library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"
#include "TextureContainer.h"


class Block
{
	Shader shader;
	VertexData3D vertices;
	Texture* textureSide;
	Texture* textureTop;

public:
	Transform trans;
	Block(const Shader& shader, Texture* textureSide, Texture* textureTop, const char* verticesPath, const char* indicesPath);

	void render(glm::mat4 view, float zoom);
};