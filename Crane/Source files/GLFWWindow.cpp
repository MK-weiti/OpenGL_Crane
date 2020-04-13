#include "GLFWWindow.h"
#include <SOIL.h>

float GLFWWindow::jibHorizontalPosition = 0.0f;
Camera camera = Camera();

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		std::cout << "Failed to load texture file\n";
		exit(1);
	}

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void GLFWWindow::windowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // without deprecated functions
	glfwWindowHint(GLFW_SAMPLES, 4);
}


void GLFWWindow::createShaders()
{
	shaderContainer.createFragmentShader("Shaders\\SimpleShaderFragment.txt", "simpleShaderFragment");
	shaderContainer.createVertexShader("Shaders\\ShaderVertexHorizontal.txt", "shaderVertexHorizontal");
	shaderContainer.createFragmentShader("Shaders\\ColorShaderFragment.txt", "colorShaderFragment");
	shaderContainer.createFragmentShader("Shaders\\TextureShaderFragment.txt", "textureShaderFragment");

	shaderContainer.createShader("shaderVertexHorizontal", "simpleShaderFragment", "sectionVerticalShader");
	shaderContainer.createShader("shaderVertexHorizontal", "colorShaderFragment", "sectionHorizontalShader");
	shaderContainer.createShader("shaderVertexHorizontal", "textureShaderFragment", "sectionHorizontalTextureShader");

	shaderContainer.createShader("shaderVertexHorizontal", "colorShaderFragment", "sectionJibShader");
}

void GLFWWindow::loadTextures()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	texContainer.loadTexture("Textures\\concrete-texture1600x1600.jpg", "concrete");
	texContainer.createTexture("concrete");
	texContainer.loadTexture("Textures\\blockSide.jpg", "blockSide");
	texContainer.createTexture("blockSide");
	texContainer.loadTexture("Textures\\blockTop.jpg", "blockTop");
	texContainer.createTexture("blockTop");
	texContainer.loadTexture("Textures\\crane_beam.jpg", "craneBeam");
	texContainer.createTexture("craneBeam");
	texContainer.loadTexture("Textures\\Map2.jpg", "Map");
	texContainer.createTexture("Map");
	texContainer.loadTexture("Textures\\glass.jpg", "Glass");
	texContainer.createTexture("Glass");
	texContainer.loadTexture("Textures\\metalTexture.jpg", "metalJib");
	texContainer.createTexture("metalJib");
	//texContainer.loadTexture("Textures\\boring_ground.jpg", "groundTex");
	//texContainer.createTexture("groundTex");
}

GLFWWindow::GLFWWindow()
{
	if (initAndCreateWindow()) throw "Window cannot be initialized.";

	createShaders();
	loadTextures();

	light = new Light();

	skybox = new Skybox("Shaders\\ShaderVertexSkyFrontBack.txt", "Shaders\\ShaderVertexSkyRightLeft.txt", "Shaders\\ShaderVertexSkyTop.txt", "Shaders\\ShaderFragmentSky.txt", "Vertices\\SkyVert.txt", "Indices\\SkyInd.txt");
	ground = new Ground("Shaders\\ShaderVertexGround.txt", "Shaders\\TextureShaderFragment.txt", "Vertices\\GroundVert.txt", "Indices\\GroundInd.txt", texContainer.getTexture("concrete"));

	
	sectionVertical = new CraneVerticalSection(numberOfVerticalParts,
		*(shaderContainer.getShader("sectionHorizontalTextureShader")), "Vertices\\VerticalCranePartVert.txt", "Indices\\VerticalCranePartInd.txt", texContainer.getTexture("craneBeam"), texContainer.getTexture("concrete"));

	sectionHorizontal = new CraneHorizontalSection(sectionVertical->partsNumber()+0.2f, numberOfHorizontalParts,
		*(shaderContainer.getShader("sectionHorizontalTextureShader")), texContainer.getTexture("concrete"), texContainer.getTexture("craneBeam"),
		texContainer.getTexture("Glass"), texContainer.getTexture("metalJib"), "Vertices\\HorizontalCranePartVert.txt", "Indices\\HorizontalCranePartInd.txt",
		"Vertices\\HorizontalCraneBaseVert.txt", "Indices\\HorizontalCraneBaseInd.txt", "Vertices\\HorizontalCraneEndVert.txt", "Indices\\HorizontalCraneEndInd.txt",
		"Vertices\\HorizontalCraneMidVert.txt", "Indices\\HorizontalCraneMidInd.txt", "Vertices\\HorizontalCraneCabinVert.txt", "Indices\\HorizontalCraneCabinInd.txt",
		"Vertices\\HorizontalCraneAtachVert.txt", "Indices\\HorizontalCraneAtachInd.txt", "Vertices\\HorizontalCraneWeightVert.txt", "Indices\\HorizontalCraneWeightInd.txt",
		"Vertices\\HorizontalCraneBasketVert.txt", "Indices\\HorizontalCraneBasketInd.txt", "Vertices\\HorizontalCraneGlassVert.txt", "Indices\\HorizontalCraneGlassInd.txt");
	
	sectionJib = new CraneJibSection(GLfloat(sectionVertical->partsNumber()+0.2f), numberOfHorizontalParts, *(shaderContainer.getShader("sectionJibShader")), *(shaderContainer.getShader("sectionHorizontalTextureShader")),
		texContainer.getTexture("metalJib"), texContainer.getTexture("craneBeam"),
		"Vertices\\JibCranePartVert.txt", "Indices\\JibCranePartInd.txt","Vertices\\JibCraneWheelVert.txt","Indices\\JibCraneWheelInd.txt",
		"Vertices\\JibCraneRailVert.txt","Indices\\JibCraneRailInd.txt","Vertices\\JibCraneLinePartVert.txt", "Indices\\JibCraneLinePartInd.txt","Vertices\\JibCraneLineEndVert.txt","Indices\\JibCraneLineEndInd.txt");
	
	blocks = new Block*[numberOfBlocks];
	for (GLuint i = 0; i < numberOfBlocks; i++)
	{
		blocks[i] = new Block(*(shaderContainer.getShader("sectionHorizontalTextureShader")), texContainer.getTexture("blockSide"), texContainer.getTexture("blockTop"), "Vertices\\BlockVert.txt", "Indices\\BlockInd.txt");
		blocks[i]->trans.move(-5.0f + 5 * i, 0.0f, -7.0f);
	}

	//constructorTestSection();

}
GLFWWindow::~GLFWWindow()
{
	delete sectionVertical;
	delete sectionHorizontal;
	delete sectionJib;
	delete skybox;
	delete ground;
	delete light;

	// test
	destructorTestSection();
	// test

	glfwTerminate();
}

void GLFWWindow::processInput(GLFWwindow* window)
{
	float rotationSpeed = 10.0f;
	float jibHorizonstalSpeed = 1.0f;
	float jibVerticalSpeed = 3.5f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotate(rotationSpeed * deltaTimef);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rotate(-rotationSpeed * deltaTimef);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) moveJibHorizontally(jibHorizonstalSpeed * deltaTimef);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) moveJibHorizontally(-jibHorizonstalSpeed * deltaTimef);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) != GLFW_PRESS) moveJibVertically(jibVerticalSpeed * deltaTimef);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_T) != GLFW_PRESS) moveJibVertically(-jibVerticalSpeed * deltaTimef);
	

	if (glfwGetKey(window, GLFW_KEY_W)) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S)) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A)) camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D)) camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE)) camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) camera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_U)) light->ProcessKeyboard(VALUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J)) light->ProcessKeyboard(VALDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Y)) light->ProcessKeyboard(AMBIENTUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_H)) light->ProcessKeyboard(AMBIENTDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z)) light->ProcessKeyboard(RUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_X)) light->ProcessKeyboard(RDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C)) light->ProcessKeyboard(GUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_V)) light->ProcessKeyboard(GDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_B)) light->ProcessKeyboard(BUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_N)) light->ProcessKeyboard(BDOWN, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { camera.ProcessMouseScroll((float) yoffset);}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool GLFWWindow::mainLoop() {
	double FPSRefresh = 1.0;
	double frameHertz = 1.0 / maxFPS;
	double lastTime = glfwGetTime();
	GLuint frameNumber = 0;

	while (!glfwWindowShouldClose(window))
	{
		double currentFrame = glfwGetTime();
		++frameNumber;
		deltaTime = currentFrame - lastFrame;
		
		while (deltaTime < frameHertz) {
			deltaTime = glfwGetTime() - lastFrame;
		}
		deltaTimef = (float)deltaTime;

		if (currentFrame - lastTime >= FPSRefresh) {
			lastTime = currentFrame;
			printf("%d ", frameNumber);
			frameNumber = 0;
		}
		lastFrame = currentFrame;


		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		processInput(window);
		mouse_callback(window);

		//test
		beforeTestRender();
		//test

		// Clear the colorbuffer
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sectionVertical->render(camera.getViewMatrix(), camera.getZoom(), light->getAmbient(), light->lights[0].getValue(), light->lights[0].getPosition(), camera.getPosition());
		sectionHorizontal->render(camera.getViewMatrix(), camera.getZoom(), light->getAmbient() + light->lights[0].getValue());
		sectionJib->render(camera.getViewMatrix(), camera.getZoom(), light->getAmbient() + light->lights[0].getValue());
		ground->render(camera.getViewMatrix(), camera.getZoom(), light->getAmbient(), light->lights[0].getValue(), light->lights[0].getPosition(), camera.getPosition());
		skybox->render(camera.getViewMatrix(), camera.getZoom(), camera.getPosition());
		for (GLuint i = 0; i < numberOfBlocks; i++) blocks[i]->render(camera.getViewMatrix(), camera.getZoom());
		

		//test
		//testRender(camera.getViewMatrix(), camera.getZoom());
		//test

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	return false;
}

bool GLFWWindow::initAndCreateWindow() {
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		return true;
	}

	windowHints();

	glEnable(GL_MULTISAMPLE);
	window = glfwCreateWindow(WIDTH, HEIGHT, windowName, nullptr, nullptr);
	if (window == nullptr) return true;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) return true;
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return false;
}

GLuint GLFWWindow::getWidth() { return WIDTH; }

GLuint GLFWWindow::getHeight() { return HEIGHT; }

void GLFWWindow::rotate(float angle)
{
	sectionHorizontal->rotate(angle);
	sectionJib->rotate(angle);
}

void GLFWWindow::moveJibHorizontally(float movement)
{
	if (jibHorizontalPosition + movement<0.0f || jibHorizontalPosition + movement>float(numberOfHorizontalParts) - 1.1f || movement == 0)return;
	sectionJib->moveJibHorizontally(movement);
	jibHorizontalPosition += movement;
}

void GLFWWindow::moveJibVertically(float movement) { sectionJib->moveJibVertically(movement); }

void GLFWWindow::mouse_callback(GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}




/*
Methods for testing
You can use them as you like
*/

void GLFWWindow::constructorTestSection()
{
	/*texContainer.loadTexture("Textures\\Map2.jpg", "Map");
	texContainer.createTexture("Map");*/
	std::cout << "Map: " << texContainer.getTexture("Map")->getTextSlot() << std::endl;
	
	cylinder = new Cylinder(*(shaderContainer.getShader("sectionHorizontalTextureShader")), texContainer.getTexture("Map"), 1, 0.5, 2, 30);
	cylinder->setTextGen(true);
	cylinder->generateObject();
	cylinder->trans.move(10, 10, 0);

	cuboid = new Cuboid(*(shaderContainer.getShader("sectionHorizontalTextureShader")), texContainer.getTexture("Map"), 1, 2, 1);
	cuboid->setTextGen(true);
	cuboid->setNormalGen(true);
	cuboid->generateObject();
	cuboid->trans.move(5, 10, 0);

	sphere = new Ellipsoid(*(shaderContainer.getShader("sectionHorizontalTextureShader")), texContainer.getTexture("Map"), 1.0f, 1.0f, 1.0f, 15, 30);
	sphere->setTextGen(true);
	sphere->generateObject();
	sphere->trans.move(10, 5, 5);
}

void GLFWWindow::destructorTestSection()
{
	delete cylinder;
	delete cuboid;
	delete sphere;
}

void GLFWWindow::beforeTestRender()
{
}

void GLFWWindow::testRender(glm::mat4 view, float zoom)
{
	cylinder->render(view, zoom);
	cuboid->render(view, zoom, light->getAmbient(), light->lights[0].getValue(), light->lights[0].getPosition(), camera.getPosition());
	sphere->render(view, zoom);
}