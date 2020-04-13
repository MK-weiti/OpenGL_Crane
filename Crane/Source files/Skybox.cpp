#include "Skybox.h"

float fscale = 40.0f;

Skybox::Skybox(const char* vertexPathFB, const char* vertexPathRL, const char* vertexPathT, const char* fragmentPath, const char* verticesPath, const char* indicesPath)
	:shaderFB(vertexPathFB, fragmentPath), shaderRL(vertexPathRL, fragmentPath), shaderT(vertexPathT, fragmentPath), vertices(verticesPath, indicesPath), transFB(shaderFB), transRL(shaderRL), transT(shaderT)
{
	transFB.scale(fscale, fscale, fscale);
	transFB.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transRL.scale(fscale, fscale, fscale);
	transRL.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	transT.scale(fscale, fscale, fscale);
	transT.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	texContainer.loadTexture("Textures\\darkcity_ft.jpg", "frontTex");
	texContainer.createTexture("frontTex");
	txfront = texContainer.getTexture("frontTex");

	texContainer.loadTexture("Textures\\darkcity_bk.jpg", "backTex");
	texContainer.createTexture("backTex");
	txback = texContainer.getTexture("backTex");

	texContainer.loadTexture("Textures\\darkcity_up.jpg", "topTex");
	texContainer.createTexture("topTex");
	txtop = texContainer.getTexture("topTex");

	texContainer.loadTexture("Textures\\darkcity_lf.jpg", "leftTex");
	texContainer.createTexture("leftTex");
	txleft = texContainer.getTexture("leftTex");

	texContainer.loadTexture("Textures\\darkcity_rt.jpg", "rightTex");
	texContainer.createTexture("rightTex");
	txright = texContainer.getTexture("rightTex");
}

Skybox::~Skybox() {}

void Skybox::render(glm::mat4 view, float zoom, glm::vec3 position)
{
	shaderFB.use();
	
	
	transFB.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	transFB.setView(view);
	transFB.translate(0.0f, fscale/4, 0.0f);
	transFB.translate(position.x, position.y - 3.7f, position.z - 10.0f); //making it stationary
	transFB.runAll();

	shaderFB.setInt("rotatesky", -1);
	txfront->prepareRenderTexture();
	vertices.drawPart(0);
	vertices.drawPart(1);

	shaderFB.setInt("rotatesky", 1);
	txback->prepareRenderTexture();
	vertices.drawPart(4);
	vertices.drawPart(5);

	////////////////////////////////////////////////////////////
	shaderT.use();

	transT.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	transT.setView(view);
	transT.translate(0.0f, fscale/4, 0.0f);
	transT.translate(position.x, position.y - 3.7f, position.z - 10.0f); //making it stationary
	transT.runAll();

	txtop->prepareRenderTexture();
	vertices.drawPart(2);
	vertices.drawPart(3);

	////////////////////////////////////////////////////////////
	shaderRL.use();

	transRL.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	transRL.setView(view);
	transRL.translate(0.0f, fscale/4, 0.0f);
	transRL.translate(position.x, position.y - 3.7f, position.z - 10.0f); //making it stationary
	transRL.runAll();

	shaderRL.setInt("rotatesky", -1);
	txright->prepareRenderTexture();
	vertices.drawPart(12);
	vertices.drawPart(13);
	
	shaderRL.setInt("rotatesky", 1);
	txleft->prepareRenderTexture();
	vertices.drawPart(8);
	vertices.drawPart(9);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//vertices.draw(true);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}