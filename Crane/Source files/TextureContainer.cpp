#pragma once
#include "TextureContainer.h"
#include <Shader.h>

TextureContainer::TextureIDInGL TextureContainer::textureGLID;

TextureContainer::TextureContainer()
{}

TextureContainer::~TextureContainer()
{
	for (auto it : textures) {
		if(it.second->image != nullptr) SOIL_free_image_data(it.second->image);
		if (it.second->m_isGenerated) glDeleteTextures(1, &it.second->textureID);
	}
}

Texture::Texture()
	:m_isGenerated(false), image(nullptr), textureID(0), textureSlot(0), width(0), height(0)
{}

//void TextureContainer::setGLRepeat() {
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//}
//
//void TextureContainer::setGLClamptoedge() {
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//}


void TextureContainer::loadTexture(const char* path, const std::string& textureName, int textureType)
{
	if (textures.find(textureName) != textures.end()) {
		std::cout << "Texture with this name already exist : " << textureName << std::endl;
		return;
	}

	Texture* tex = new Texture();

	tex->image = SOIL_load_image(path, &tex->width, &tex->height, 0, textureType);
	if (tex->image == nullptr)
	{
		std::cout << "Failed to load texture file" << std::endl;
		delete tex;
		return;
	}
	textures[textureName] = tex;
}

void TextureContainer::createTexture(const std::string& textureName, const GLenum format, const GLint internalFormat, const bool freeImage, const bool unbind)
{
	if (textures.find(textureName) == textures.end()) {
		std::cout << "Texture with this name do not exist : " << textureName << std::endl;
		return;
	}

	Texture* tex = textures[textureName];
	if (tex->m_isGenerated || tex->image == nullptr) {
		std::cout << "Texture is already generated or there is no image" << std::endl;
		return;
	}
	GLuint texGLID;	// two times, because other texture is used somewhere else
	if (textureGLID.getNextIndex(texGLID) || textureGLID.getNextIndex(texGLID)) {
		std::cout << "Texture buffor is full. Cannot create texture. Please delete some texture to make a space for a new one." << std::endl;
		return;
	}

	glGenTextures(1, &tex->textureID);
	glActiveTexture(texGLID);
	tex->textureSlot = texGLID;

	
	glBindTexture(GL_TEXTURE_2D, tex->textureID);
	//seems like glTexParameteri only works from this point
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tex->width, tex->height, 0, format, GL_UNSIGNED_BYTE, tex->image);
	glGenerateMipmap(GL_TEXTURE_2D);
	tex->m_isGenerated = true;

	if (freeImage) {
		SOIL_free_image_data(tex->image);
		tex->image = nullptr;
	}
	if(unbind) glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureContainer::setTexParameteri(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

void TextureContainer::deleteTexture(std::string& textureName)
{
	if (textures.find(textureName) == textures.end()) {
		std::cout << "Texture with this name do not exist : " << textureName << std::endl;
		return;
	}

	Texture* tex = textures[textureName];

	if(tex->image != nullptr) SOIL_free_image_data(tex->image);
	if(tex->m_isGenerated) glDeleteTextures(1, &tex->textureID);
	textures.erase(textureName);
	delete tex;
}

void TextureContainer::freeImage(std::string& textureName)
{
	Texture* tex = textures[textureName];
	if (tex->m_isGenerated == false) {
		deleteTexture(textureName);
	}
	else if (tex->image != nullptr) {
		SOIL_free_image_data(tex->image);
		tex->image = nullptr;
	}
}

Texture::Texture(const Texture& texture)
	:m_isGenerated(texture.m_isGenerated), image(texture.image), textureID(texture.textureID), width(texture.width), height(texture.height)
{}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

bool Texture::isGenerated()
{
	return m_isGenerated;
}

bool Texture::hasImage()
{
	if(image == nullptr) return false;
	return true;
}

void Texture::prepareRenderTexture()
{
	if (m_isGenerated) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}

GLuint Texture::getTextSlot()
{
	return textureSlot;
}

TextureContainer::TextureIDInGL::TextureIDInGL()
	:check(new bool[GL_MAX_TEXTURE_UNITS]), index(0)
{
	for (GLuint i = 0; i < GL_MAX_TEXTURE_UNITS; ++i) {
		check[i] = false;
	}
}

TextureContainer::TextureIDInGL::~TextureIDInGL()
{
	delete[] check;
}

bool TextureContainer::TextureIDInGL::getNextIndex(GLuint& slot)
{
	GLuint controlSum = 0;
	while (check[index] && controlSum < GL_MAX_TEXTURE_UNITS) {
		++index;
		++controlSum;
		if (index == GL_MAX_TEXTURE_UNITS) {
			index = 0;
		}
	}
	if (controlSum == GL_MAX_TEXTURE_UNITS) return true;

	slot = GL_TEXTURE0 + 1 + index;
	check[index++] = true;

	if (index == GL_MAX_TEXTURE_UNITS) {
		index = 0;
	}

	return false;
}

bool TextureContainer::TextureIDInGL::deleteIndex(const GLuint& slot)
{
	if (check[slot] == false) return true;
	check[slot] = false;
	return true;
}

Texture* TextureContainer::getTexture(const std::string& textureName)
{
	if (textures.find(textureName) == textures.end()) {
		std::cout << "Texture not found." << std::endl;
		return new Texture();
	}

	Texture* tex = textures[textureName];
	return tex;
}

