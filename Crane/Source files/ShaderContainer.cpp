#include "ShaderContainer.h"

ShaderContainer::ShaderContainer() {}

ShaderContainer::~ShaderContainer()
{
	for (auto it : vertexShaders) {
		glDeleteShader(it.second);
	}

	for (auto it : fragmentShaders) {
		glDeleteShader(it.second);
	}

	for (auto it : shaders) {
		it.second->shaderDelete();
		delete it.second;
	}

}


bool ShaderContainer::createVertexShader(const char* path, const std::string& keyName)
{
	if (shaderVertexKeyExistError(keyName)) return true;
	
	std::string vertexCode;
	std::ifstream vShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(path);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER_CONTAINER::VERTEX_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return true;
	}
	const char* vShaderCode = vertexCode.c_str();

	// 2. compile shaders
	GLuint vertex;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	if (checkCompileErrors(vertex, "VERTEX")) return true;

	vertexShaders[keyName] = vertex;

	return false;
}

bool ShaderContainer::createFragmentShader(const char* path, const std::string& keyName)
{
	if (shaderFragmentKeyExistError(keyName)) return true;
	
	std::string fragmentCode;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		fShaderFile.open(path);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		fShaderFile.close();
		// convert stream into string
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER_CONTAINER::FRAGMENT_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return true;
	}
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	GLuint fragment;

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	if(checkCompileErrors(fragment, "FRAGMENT")) return true;

	fragmentShaders[keyName] = fragment;

	return false;
}

bool ShaderContainer::createShader(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& keyName)
{
	if (shaderKeyExistError(keyName)) return true;
	if (shaderVertexKeyNotExistError(vertexShaderName)) return true;
	if (shaderFragmentKeyNotExistError(fragmentShaderName)) return true;

	shaders[keyName] = new Shader(vertexShaders[vertexShaderName], fragmentShaders[fragmentShaderName]);
	if (!shaders[keyName]->isGood()) {
		delete shaders[keyName];
		shaders.erase(keyName);
		return true;
	}
	
	return false;
}

bool ShaderContainer::createShader(const GLuint& vertexShaderID, const GLuint& fragmentShaderID, const std::string& keyName)
{
	if (shaderKeyExistError(keyName)) return true;


	shaders[keyName] = new Shader(vertexShaderID, fragmentShaderID);
	if (!shaders[keyName]->isGood()) {
		delete shaders[keyName];
		shaders.erase(keyName);
		return true;
	}

	return false;
}


bool ShaderContainer::deleteVertexShader(const std::string& keyName)
{
	if (shaderVertexKeyNotExistError(keyName)) return true;

	GLuint ID = vertexShaders[keyName];
	vertexShaders.erase(keyName);
	glDeleteShader(ID);

	return false;
}

bool ShaderContainer::deleteFragmentShader(const std::string& keyName)
{
	if (shaderFragmentKeyNotExistError(keyName)) return true;

	GLuint ID = fragmentShaders[keyName];
	fragmentShaders.erase(keyName);
	glDeleteShader(ID);

	return false;
}

bool ShaderContainer::deleteShader(const std::string& keyName)
{
	if (shaderKeyNotExistError(keyName)) return true;

	Shader* tmp = shaders[keyName];
	tmp->shaderDelete();
	delete tmp;
	shaders.erase(keyName);

	return false;
}


GLuint ShaderContainer::getShaderID(const std::string& keyName) const
{	
	if (shaders.find(keyName) == shaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::SHADER::KEY_DO_NOT_EXIST" << std::endl;
		return true;
	}

	return shaders.at(keyName)->getID();
}

Shader* ShaderContainer::getShader(const std::string& keyName) const
{
	if (shaders.find(keyName) == shaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::SHADER::KEY_DO_NOT_EXIST" << std::endl;
		return nullptr;
	}

	return shaders.at(keyName);
}


// check errors

bool ShaderContainer::checkCompileErrors(const unsigned int& shader, const std::string& type) const
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			return true;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			return true;
		}
	}

	return false;
}


bool ShaderContainer::shaderKeyExistError(const std::string& keyName)
{
	if (shaders.find(keyName) != shaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::SHADER::KEY_ALREADY_EXIST" << std::endl;
		return true;
	}
	return false;
}

bool ShaderContainer::shaderFragmentKeyExistError(const std::string& keyName)
{
	if (fragmentShaders.find(keyName) != fragmentShaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::FRAGMENT_SHADER::KEY_ALREADY_EXIST" << std::endl;
		return true;
	}
	return false;
}

bool ShaderContainer::shaderVertexKeyExistError(const std::string& keyName)
{
	if (vertexShaders.find(keyName) != vertexShaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::VERTEX_SHADER::KEY_ALREADY_EXIST" << std::endl;
		return true;
	}
	return false;
}


bool ShaderContainer::shaderKeyNotExistError(const std::string& keyName)
{
	if (shaders.find(keyName) == shaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::SHADER::KEY_DO_NOT_EXIST" << std::endl;
		return true;
	}
	return false;
}

bool ShaderContainer::shaderFragmentKeyNotExistError(const std::string& keyName)
{
	if (fragmentShaders.find(keyName) == fragmentShaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::VERTEX_SHADER::KEY_DO_NOT_EXIST" << std::endl;
		return true;
	}
	return false;
}

bool ShaderContainer::shaderVertexKeyNotExistError(const std::string& keyName)
{
	if (vertexShaders.find(keyName) == vertexShaders.end()) {
		std::cout << "ERROR::SHADER_CONTAINER::VERTEX_SHADER::KEY_DO_NOT_EXIST" << std::endl;
		return true;
	}
	return false;
}
