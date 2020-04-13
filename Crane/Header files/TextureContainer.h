#pragma once

#define GLEW_STATIC // to mark that we use static library
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <map>
#include <string>
#include <iostream>

class TextureContainer;

class Texture {
	friend TextureContainer;

	bool m_isGenerated;
	unsigned char* image;
	GLuint textureID;
	GLuint textureSlot;
	int width;
	int height;

public:
	Texture();
	Texture(const Texture& texture);
	int getWidth();
	int getHeight();
	GLuint getTextSlot();
	bool isGenerated();
	bool hasImage();

	void prepareRenderTexture();
};

class TextureContainer
{
	class TextureIDInGL {
		bool* check;
		GLuint index;

	public:
		TextureIDInGL();
		~TextureIDInGL();

		bool getNextIndex(GLuint& slot);
		bool deleteIndex(const GLuint& slot);
	};

	std::map<std::string, Texture*> textures;
	static TextureIDInGL textureGLID;

public:
	TextureContainer();
	~TextureContainer();

	void loadTexture(const char* path, const std::string& name, int textureType = SOIL_LOAD_RGB);

	void createTexture(const std::string& textureName, const GLenum format = GL_RGB, const GLint internalFormat = GL_RGB, \
		const bool freeImage = true, const bool unbind = true);

	void deleteTexture(std::string& textureName);
	void freeImage(std::string& textureName);

	void setTexParameteri(GLenum target, GLenum pname, GLint param);
	//void setGLRepeat();
	//void setGLClamptoedge();

	Texture* getTexture(const std::string& textureName);
};
