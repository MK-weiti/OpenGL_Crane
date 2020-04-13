#pragma once
#define GLEW_STATIC // to mark that we use static library
#include <iostream>

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include <windows.h>

#include "ShaderContainer.h"
#include "Camera.h"
#include "CraneVerticalSection.h"
#include "CraneHorizontalSection.h"
#include "CraneJibSection.h"
#include "Skybox.h"
#include "Ground.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Ellipsoid.h"
#include "TextureContainer.h"
#include "Block.h"
#include "Light.h"

class GLFWWindow
{
	ShaderContainer shaderContainer;
	CraneVerticalSection* sectionVertical;
	CraneHorizontalSection* sectionHorizontal;
	CraneJibSection *sectionJib;
	Skybox *skybox;
	Ground *ground;
	Block** blocks;

	GLuint WIDTH = 800;
	GLuint HEIGHT = 600;
	GLuint numberOfVerticalParts = 5;
	GLuint numberOfHorizontalParts = 5;
	GLuint numberOfBlocks = 3;

	const char* windowName = "Crane project";

	//Crane movement variable
	static float jibHorizontalPosition;

	// timing
	double deltaTime = 0.0;
	float deltaTimef = 0.0f;
	double lastFrame = 0.0;

	GLFWwindow* window;
	double lastX = WIDTH / 2.0f;
	double lastY = HEIGHT / 2.0f;
	bool firstMouse = true;

	GLfloat maxFPS = 60.0;

	bool initAndCreateWindow();
	void windowHints();

	// test section
	void constructorTestSection();
	void destructorTestSection();
	void beforeTestRender();
	void testRender(glm::mat4 view, float zoom);
	
	Cylinder* cylinder = nullptr;
	Cuboid* cuboid = nullptr;
	Ellipsoid* sphere = nullptr;
	TextureContainer texContainer;

	Light *light;

public:
	void createShaders();
	void loadTextures();
	GLFWWindow();
	~GLFWWindow();
	bool mainLoop();

	GLuint getWidth();
	GLuint getHeight();
	void rotate(float angle);
	void moveJibHorizontally(float movement);
	void moveJibVertically(float movement);
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window);
};