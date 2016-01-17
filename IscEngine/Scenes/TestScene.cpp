#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Graphics/Models/Loaders/ObjLoader.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Views/Modelview.hpp"

Camera camera;

mat4 P;
mat4 V;

bool rotatingCamera = false;
bool shadows = false;

GLuint textureId[2];
GLuint depthTexture;

int mapsize = 1;
float separation = 5.f;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	//shader = Shader();
	shader.loadFromFiles(RESOURCE_PATH + "ShadowMapping_SimpleVersion.vertexshader", RESOURCE_PATH + "ShadowMapping_SimpleVersion.fragmentshader");

	//shShadowMap = Shader();
	shShadowMap.loadFromFiles(RESOURCE_PATH + "shShadowMap.vsh", RESOURCE_PATH + "shShadowMap.fsh");

	camera.setPosition(vec3(mapsize * separation / 2 - 3, 10.5, mapsize * separation / 2 - 3));
	camera.lookAt(vec3(0, 0, 0));

	P = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 1000.0f);

	vector<unsigned int> objIndices;
	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUvs;
	std::vector<glm::vec3> objNormals;

	loadModel(RESOURCE_PATH + "map.fbx", objIndices, objVertices, objUvs, objNormals);

	Log::cout << "Vertices: " << ((objVertices.size() > objIndices.size()) ? objVertices.size() : objIndices.size() * mapsize * mapsize) << endl;

	mesh[0] = new Mesh(objVertices);
	if (objIndices.size() > 0) mesh[0]->addIndexes(objIndices);
	if (objNormals.size() > 0) mesh[0]->addNormals(objNormals);
	if (objUvs.size() > 0) mesh[0]->addUVs(objUvs);

	objIndices.clear();
	objVertices.clear();
	objUvs.clear();
	objNormals.clear();

	loadModel(RESOURCE_PATH + "floor_maya.fbx", objIndices, objVertices, objUvs, objNormals);

	mesh[1] = new Mesh(objVertices);
	if (objIndices.size() > 0) mesh[1]->addIndexes(objIndices);
	if (objNormals.size() > 0) mesh[1]->addNormals(objNormals);
	if (objUvs.size() > 0) mesh[1]->addUVs(objUvs);

	GLuint textureGl;
	sf::Image image;

	if (!image.loadFromFile(RESOURCE_PATH + "katarina_base_diffuse.png")) {

		Log::cout << "Texture loading error" << std::endl;

	} else {

		glGenTextures(1, &textureGl);
		glBindTexture(GL_TEXTURE_2D, textureGl);

		glTexImage2D(
			GL_TEXTURE_2D,
			0, //mip-map level
			GL_RGBA, //We want the internal texture to have RGBA components
			image.getSize().x, image.getSize().y, // size of texture
			0, //border (0=no border, 1=border)
			GL_RGBA, //format of the external texture data
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr() //pointer to array of pixel data
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		textureId[0] = textureGl;

	}

	textureGl;
	image;

	if (!image.loadFromFile(RESOURCE_PATH + "textura.png")) {

		Log::cout << "Texture loading error" << std::endl;

	} else {

		glGenTextures(1, &textureGl);
		glBindTexture(GL_TEXTURE_2D, textureGl);

		glTexImage2D(
			GL_TEXTURE_2D,
			0, //mip-map level
			GL_RGBA, //We want the internal texture to have RGBA components
			image.getSize().x, image.getSize().y, // size of texture
			0, //border (0=no border, 1=border)
			GL_RGBA, //format of the external texture data
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr() //pointer to array of pixel data
			);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		textureId[1] = textureGl;

	}

	///////////////////////////////////////////////////////

	FrameBuffer::bind(&shadowFrameBuffer);
	/*glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);*/

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Function for testing shadow
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	// We dont want color, only depth
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Log::cout << "Error framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

	FrameBuffer::unbind();

	cout << "Fin carga Escena" << endl;

}

void TestScene::processEvent(const sf::Event& event) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed:
			sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) this->endScene();
			if (event.key.code == sf::Keyboard::Space) shadows = !shadows;
			if (event.key.code == sf::Keyboard::B) this->endScene(new Scenes::TestScene(window));
			break;

	}

}

void TestScene::update() {

	fpsCount++;
	fpsTime += deltaTime;
	if (fpsTime.asSeconds() >= 1.f) {

		window->setTitle("Fps: " + std::to_string(fpsCount));
		fpsTime -= sf::seconds(1.f);
		fpsCount = 0;

	}

	if (window->isFocused()) processInput();

	V = camera.getView();

}

void TestScene::processInput() {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->window->isFocused()) {

		float sensibilidad = 0.2f;

		this->window->setMouseCursorVisible(false);
		sf::Vector2i centerWindow = sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2);
		sf::Vector2i diferencia = centerWindow - sf::Mouse::getPosition(*this->window);
		if (diferencia.x != 0 || diferencia.y != 0) {

			camera.setRotation(vec2(camera.getRotation().x + diferencia.y * sensibilidad, camera.getRotation().y + diferencia.x * sensibilidad));
			sf::Mouse::setPosition(centerWindow, *this->window);

		}

	} else {

		this->window->setMouseCursorVisible(true);

	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && window->isFocused()) {

		camera.setPosition(vec3(camera.getPosition().x + camera.getDirection().x * 20 * deltaTime.asSeconds(),
								camera.getPosition().y + camera.getDirection().y * 20 * deltaTime.asSeconds(),
								camera.getPosition().z + camera.getDirection().z * 20 * deltaTime.asSeconds()));

	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {

		camera.setPosition(vec3(camera.getPosition().x - camera.getDirection().x * 20 * deltaTime.asSeconds(),
								camera.getPosition().y - camera.getDirection().y * 20 * deltaTime.asSeconds(),
								camera.getPosition().z - camera.getDirection().z * 20 * deltaTime.asSeconds()));

	}

}

bool moveRight = false;
float pos = 20;

void TestScene::render() {

	mat4 depthBiasVP;

	if (shadows) {

		// Render to texture
		FrameBuffer::bind(&shadowFrameBuffer);
		glViewport(0, 0, 2048, 2048);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_CULL_FACE);

		Shader::bind(&shShadowMap);

		float size = 80;
		float viewDistance = 150;
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-size, size, -size, size, -viewDistance, viewDistance);
		//glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50000.0f);
		glm::mat4 depthViewMatrix = glm::lookAt(vec3(pos, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		if (moveRight) pos += 5 * deltaTime.asSeconds(); else pos -= 5 * deltaTime.asSeconds();
		if (moveRight && pos > 20) moveRight = !moveRight;
		if (!moveRight && pos < -20) moveRight = !moveRight;

		shShadowMap.setUniformMatrix("V", &depthViewMatrix[0][0]);
		shShadowMap.setUniformMatrix("P", &depthProjectionMatrix[0][0]);

		/*mat4 model(1.f);
		model = glm::translate(vec3(0, 2, 0));
		model = glm::scale(model, vec3(5, 5, 5));
		shShadowMap.setUniformMatrix("M", &model[0][0]);
		mesh[1]->render(GL_TRIANGLES);*/

		for (int i = 0; i < mapsize; i++) {
			for (int j = 0; j < mapsize; j++) {

				mat4 model = ModelView::getModelView(vec3(i * separation, 2.0f, j * separation),
										  vec3(0, radians(i * 25.f + j * 25.f), 0));

				shShadowMap.setUniformMatrix("M", &model[0][0]);
				mesh[0]->render(GL_TRIANGLES);
			}
		}

		Shader::unbind();

		glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;
		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);
		depthBiasVP = biasMatrix * depthVP;

	}

	////////////////////////////////////////////////////////
	
	FrameBuffer::unbind();
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);

	Shader::bind(&shader);

	shader.setUniformMatrix("V", &V[0][0]);
	shader.setUniformMatrix("P", &P[0][0]);
	vec3 cameraPosition = camera.getPosition();
	shader.setUniform("LightPosition_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);
	
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId[1]);
	shader.setUniform("myTextureSampler", 0);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	shader.setUniform("shadowMap", 1);

	if (shadows) shader.setUniformMatrix("DepthBiasVP", &depthBiasVP[0][0]);

	//mat4 model2(1.f);
	//model2 = glm::translate(vec3(8, 2, 8));
	//model2 = glm::scale(model2, vec3(5, 5, 5));
	//shader.setUniformMatrix("M", &model2[0][0]);
	//mesh[1]->render(GL_TRIANGLES);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId[1]);

	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {

			mat4 model = ModelView::getModelView(vec3(i * separation, 2.0f, j * separation),
									  vec3(0, radians(i * 25.f + j * 25.f), 0));

			shader.setUniformMatrix("M", &model[0][0]);
			mesh[0]->render(GL_TRIANGLES);
		}
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	Shader::unbind();
	//*/

	window->pushGLStates();
	sf::CircleShape a(50.f);
	a.setFillColor(sf::Color::Red);
	window->draw(a);
	window->popGLStates();

	window->display();

}

TestScene::~TestScene() {

	cout << "Destructor TESTscene" << endl;

	delete mesh[0]; mesh[0] = nullptr;
	delete mesh[1]; mesh[1] = nullptr;

}