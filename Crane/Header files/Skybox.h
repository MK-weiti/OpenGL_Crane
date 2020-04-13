#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"
#include "TextureContainer.h"

class Skybox
{
	Shader shaderFB;
	Shader shaderRL;
	Shader shaderT;
	VertexData3D vertices;
	TextureContainer texContainer;
	Texture *txfront;
	Texture *txback;
	Texture *txtop;
	Texture *txleft;
	Texture *txright;

public:
	Transform transFB, transRL, transT;

	Skybox(const char* vertexPathFB, const char* vertexPathRL, const char* vertexPathT, const char* fragmentPath, const char* verticesPath, const char* indicesPath);
	~Skybox();

	void render(glm::mat4 view, float zoom, glm::vec3 position);
};