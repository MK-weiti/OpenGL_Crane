#include "Transform.h"

Transform::Transform(Shader &shader)
	:model(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)), moveMatrix(glm::mat4(1.0f)), shader(shader), scaleMatrix(glm::mat4(1.0f)), rotationMatrix(glm::mat4(1.0f)), \
	modelLoc(glGetUniformLocation(shader.getID(), "model")), viewLoc(glGetUniformLocation(shader.getID(), "view")), scaleLoc(glGetUniformLocation(shader.getID(), "scaleMatrix")), rotationLoc(glGetUniformLocation(shader.getID(), "rotationMatrix")) {}

void Transform::rotate(GLfloat rad, GLfloat x, GLfloat y, GLfloat z) 
{
	model = glm::rotate(model, rad, glm::vec3(x, y, z));
}
void Transform::basicRotate(GLfloat rad, GLfloat x, GLfloat y, GLfloat z)  // obrot obiektu wokol jego srodka
{
	rotationMatrix = glm::rotate(rotationMatrix, rad, glm::vec3(x, y, z));
}
void Transform::scale(GLfloat x, GLfloat y, GLfloat z)
{
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(x, y, z));
}

void Transform::perspective(GLfloat rad, GLfloat ratio, GLfloat near, GLfloat far)
{
	projection = glm::perspective(rad, ratio, near, far);
}
void Transform::translate(GLfloat x, GLfloat y, GLfloat z)
{
	view = glm::translate(view, glm::vec3(x, y, z));
}

void Transform::move(GLfloat x, GLfloat y, GLfloat z)
{
	moveMatrix = glm::translate(moveMatrix, glm::vec3(x, y, z));
}

void Transform::setView(glm::mat4 view) { this->view = view; }

void Transform::runRotate()
{
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Transform::runScale()
{
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}
void Transform::runBasicRotation() // obrot obiektu wokol jego srodka
{
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}
void Transform::runPerspective()
{
	shader.setMat4("projection", projection);
}

void Transform::runTranslate()
{
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void Transform::runMove()
{
	shader.setMat4("moveMatrix", moveMatrix);
}

void Transform::runAll()
{
	runBasicRotation();
	runRotate();
	runPerspective();
	runTranslate();
	runMove();
	runScale();
}

void Transform::resetRotate()
{
	model = glm::mat4(1.0f);
}
void Transform::resetBasicRotate()
{
	rotationMatrix = glm::mat4(1.0f);
}
void Transform::resetPerspective()
{
	projection = glm::mat4(1.0f);
}
void Transform::resetTranslate()
{
	view = glm::mat4(1.0f);
}
void Transform::resetScale()
{
	scaleMatrix = glm::mat4(1.0f);
}
void Transform::resetMove()
{
	moveMatrix = glm::mat4(1.0f);
}
void Transform::resetAll()
{
	resetRotate();
	resetPerspective();
	resetTranslate();
	resetScale();
	resetMove();
	resetBasicRotate();
}

void Transform::rotateAndRun(GLfloat rad, GLfloat x, GLfloat y, GLfloat z)
{
	model = glm::rotate(model, rad, glm::vec3(x, y, z));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Transform::perspectiveAndRun(GLfloat rad, GLfloat ratio, GLfloat near, GLfloat far)
{
	projection = glm::perspective(rad, ratio, near, far);
	shader.setMat4("projection", projection);
}

void Transform::translateAndRun(GLfloat x, GLfloat y, GLfloat z)
{
	view = glm::translate(view, glm::vec3(x, y, z));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}
void Transform::scaleAndRun(GLfloat x, GLfloat y, GLfloat z)
{
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(x, y, z));
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}
void Transform::moveAndRun(GLfloat x, GLfloat y, GLfloat z)
{
	moveMatrix = glm::translate(moveMatrix, glm::vec3(x, y, z));
	shader.setMat4("moveMatrix", moveMatrix);
}
void Transform::basicRotateAndRun(GLfloat rad, GLfloat x, GLfloat y, GLfloat z) 
{
	rotationMatrix = glm::rotate(rotationMatrix, rad, glm::vec3(x, y, z));
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}
void Transform::changeShader(Shader& shader)
{
	this->shader = shader;
	modelLoc = glGetUniformLocation(shader.getID(), "model");
	viewLoc = glGetUniformLocation(shader.getID(), "view");
}

void Transform::changeShaderAndReset(Shader& shader)
{
	changeShader(shader);
	resetAll();
}


