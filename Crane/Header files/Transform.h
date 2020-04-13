#pragma once

#define GLEW_STATIC // to mark that we use static library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Transform
{
	glm::mat4 moveMatrix;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	Shader shader;

	GLuint modelLoc;
	GLuint viewLoc;
	GLuint scaleLoc;
	GLuint rotationLoc;
public:
	Transform(Shader& shader);

	// do not try with all x, y, z = 0
	void rotate(GLfloat rad, GLfloat x, GLfloat y, GLfloat z);
	void perspective(GLfloat rad, GLfloat ratio, GLfloat near, GLfloat far);
	void translate(GLfloat x, GLfloat y, GLfloat z);	// move the object
	void move(GLfloat x, GLfloat y, GLfloat z);

	void setView(glm::mat4 view);

	void runRotate();
	void runScale();
	void runBasicRotation();
	void runPerspective();
	void runTranslate();
	void runMove();
	void runAll();	// in default order

	void resetRotate();
	void resetBasicRotate();
	void resetPerspective();
	void resetTranslate();
	void resetScale();
	void resetMove();
	void resetAll();

	void rotateAndRun(GLfloat rad, GLfloat x, GLfloat y, GLfloat z);
	void perspectiveAndRun(GLfloat rad, GLfloat ratio, GLfloat near, GLfloat far);
	void translateAndRun(GLfloat x, GLfloat y, GLfloat z);
	void scaleAndRun(GLfloat x, GLfloat y, GLfloat z);
	void moveAndRun(GLfloat x, GLfloat y, GLfloat z);
	void basicRotateAndRun(GLfloat rad, GLfloat x, GLfloat y, GLfloat z);
	void basicRotate(GLfloat rad, GLfloat x, GLfloat y, GLfloat z);  // obrot obiektu wokol jego srodka
	void scale(GLfloat x, GLfloat y, GLfloat z);
	void changeShader(Shader& shader);
	void changeShaderAndReset(Shader& shader);
};

