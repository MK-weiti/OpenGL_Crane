#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>
#include <Shader.h>

class ShaderContainer
{
	std::map<std::string, GLuint> vertexShaders;
	std::map<std::string, GLuint> fragmentShaders;
	std::map<std::string, Shader*> shaders;

	bool checkCompileErrors(const unsigned int& shader, const std::string& type) const;
	bool shaderFragmentKeyNotExistError(const std::string& keyName);
	bool shaderVertexKeyNotExistError(const std::string& keyName);
	bool shaderFragmentKeyExistError(const std::string& keyName);
	bool shaderVertexKeyExistError(const std::string& keyName);
	bool shaderKeyNotExistError(const std::string& keyName);

public:
	ShaderContainer();
	~ShaderContainer();

	GLuint getShaderID(const std::string& keyName) const;
	Shader* getShader(const std::string& keyName) const;

	bool createVertexShader(const char* path, const std::string& keyName);
	bool createFragmentShader(const char* path, const std::string& keyName);

	bool deleteVertexShader(const std::string& keyName);
	bool deleteFragmentShader(const std::string& keyName);

	bool createShader(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& keyName);
	bool shaderKeyExistError(const std::string& keyName);
	bool createShader(const GLuint& vertexShaderID, const GLuint& fragmentShaderID, const std::string& keyName);

	bool deleteShader(const std::string& keyName);
};

