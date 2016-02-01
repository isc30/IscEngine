#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Graphics/Models/Loaders/ObjLoader.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Views/Modelview.hpp"
#include "../Graphics/Shaders/PostProcess.hpp"
#include "../World/SkyBox.hpp"

Camera camera;

mat4 P;
mat4 V;

bool rotatingCamera = false;
bool shadows = true;

int mapsize = 1;
float separation = 5.f;

Shader skyShader;
SkyBox skybox;
Texture skyboxTexture;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	shader.loadFromFiles(RESOURCE_PATH + "Shaders/shader.vsh", RESOURCE_PATH + "Shaders/shader.fsh");
	shShadowMap.loadFromFiles(RESOURCE_PATH + "Shaders/shadowMapper.vsh", RESOURCE_PATH + "Shaders/shadowMapper.fsh");
	postProcessShader.loadFromFiles(RESOURCE_PATH + "Shaders/postProcess.vsh", RESOURCE_PATH + "Shaders/postProcess.fsh");

	camera.setPosition(vec3(mapsize * separation / 2 - 3, 10.5, mapsize * separation / 2 - 3));
	camera.lookAt(vec3(0, 0, 0));

	P = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 1000.0f);

	vector<unsigned int> objIndices;
	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUvs;
	std::vector<glm::vec3> objNormals;

	loadModel(RESOURCE_PATH + "Models/fbx_PuenteRomano.fbx", objIndices, objVertices, objUvs, objNormals);

	mesh[0] = new Mesh(objVertices);
	if (objIndices.size() > 0) mesh[0]->addIndices(objIndices);
	if (objNormals.size() > 0) mesh[0]->addNormals(objNormals);
	if (objUvs.size() > 0) mesh[0]->addUVs(objUvs);

	objIndices.clear();
	objVertices.clear();
	objUvs.clear();
	objNormals.clear();

	loadModel(RESOURCE_PATH + "Models/katarina.obj", objIndices, objVertices, objUvs, objNormals);

	mesh[1] = new Mesh(objVertices);
	if (objIndices.size() > 0) mesh[1]->addIndices(objIndices);
	if (objNormals.size() > 0) mesh[1]->addNormals(objNormals);
	if (objUvs.size() > 0) mesh[1]->addUVs(objUvs);

	objIndices.clear();
	objVertices.clear();
	objUvs.clear();
	objNormals.clear();

	loadModel(RESOURCE_PATH + "Models/katarina_low.obj", objIndices, objVertices, objUvs, objNormals);

	mesh[2] = new Mesh(objVertices);
	if (objIndices.size() > 0) mesh[2]->addIndices(objIndices);
	if (objNormals.size() > 0) mesh[2]->addNormals(objNormals);
	if (objUvs.size() > 0) mesh[2]->addUVs(objUvs);

	// Create StaticEntities
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			StaticEntity* entity = new StaticEntity(mesh[1]);
			entity->addMesh(50, mesh[2]);
			entity->setPosition(vec3(i * separation, 18.3f, j * separation));
			entity->setRotation(vec3(0, radians(i * 25.f + j * 25.f), 0));
			entities.push_back(entity);
		}
	}

	textures[0] = new Texture();
	if (!textures[0]->loadFromFile(RESOURCE_PATH + "Textures/katarina_base_diffuse.png")) {
		Log::cout << "Texture loading error" << std::endl;
	}

	textures[1] = new Texture();
	if (!textures[1]->loadFromFile(RESOURCE_PATH + "Textures/PiedraRomano_Difuse.jpg")) {
		Log::cout << "Texture loading error" << std::endl;
	}

	///////////////////////////////////////////////////////

	skyShader.loadFromFiles(RESOURCE_PATH + "Shaders/SkyBox.vsh", RESOURCE_PATH + "Shaders/SkyBox.fsh");
	skyboxTexture.loadCubeMap(vector<string>({
		RESOURCE_PATH + "Textures/SkyBox/right.jpg",
		RESOURCE_PATH + "Textures/SkyBox/left.jpg",
		RESOURCE_PATH + "Textures/SkyBox/top.jpg",
		RESOURCE_PATH + "Textures/SkyBox/bottom.jpg",
		RESOURCE_PATH + "Textures/SkyBox/back.jpg",
		RESOURCE_PATH + "Textures/SkyBox/front.jpg"
	}));

	///////////////////////////////////////////////////////

	shadowFrameBuffer = new FrameBuffer(2048, 2048, false, true);
	postProcessFrameBuffer = new FrameBuffer(this->window->getSize().x, this->window->getSize().y);

	//////////////////////////////////////////////////////

	cout << "Fin carga Escena" << endl;

}

void TestScene::processEvent(const sf::Event& event) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed:
			sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) this->endScene();
			//if (event.key.code == sf::Keyboard::B) this->endScene(new Scenes::TestScene(window));
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

	for (auto it = entities.begin(), end = entities.end(); it != end; ++it) {

		vec3 currentRotation = (*it)->getRotation();
		currentRotation.y += radians(45.f * deltaTime.asSeconds());
		(*it)->setRotation(currentRotation);

	}

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

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && window->isFocused()) {

		camera.setPosition(vec3(camera.getPosition().x - camera.getDirection().x * 20 * deltaTime.asSeconds(),
								camera.getPosition().y - camera.getDirection().y * 20 * deltaTime.asSeconds(),
								camera.getPosition().z - camera.getDirection().z * 20 * deltaTime.asSeconds()));

	}

}

bool moveRight = false;
float pos = 20;

float wat = 0;

struct LightSource {

	vec3 position_worldspace;
	//vec3 direction_cameraspace;
	vec3 color;
	float power;

};

void TestScene::render() {

	mat4 depthBiasVP;

	if (shadows) {

		// Render to texture
		FrameBuffer::bind(shadowFrameBuffer);
		glViewport(0, 0, shadowFrameBuffer->getTexture()->getWidth(), shadowFrameBuffer->getTexture()->getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glDisable(GL_CULL_FACE);

		Shader::bind(&shShadowMap);

		float size = 80;
		float viewDistance = 150;
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-size, size, -size, size, -viewDistance, viewDistance);
		//glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50000.0f);
		glm::mat4 depthViewMatrix = glm::lookAt(vec3(-4.15f, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		/*if (moveRight) pos += 5 * deltaTime.asSeconds(); else pos -= 5 * deltaTime.asSeconds();
		if (moveRight && pos > 20) moveRight = !moveRight;
		if (!moveRight && pos < -20) moveRight = !moveRight;

		Log::cout << pos << endl;*/

		shShadowMap.setUniformMatrix("V", &depthViewMatrix[0][0]);
		shShadowMap.setUniformMatrix("P", &depthProjectionMatrix[0][0]);

		glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;
		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);
		depthBiasVP = biasMatrix * depthVP;

		for (int i = 0; i < 5; i++) {
			mat4 model = ModelView::getModelView(vec3(0, 0, i * 28), vec3(0,0,0), vec3(2,2,2));
			shShadowMap.setUniformMatrix("M", &model[0][0]);
			mesh[0]->render(GL_TRIANGLES);
		}

		mat4 VP = depthVP;
		for (auto it = entities.begin(), end = entities.end(); it != end; ++it) {
			(*it)->render(VP);
		}

		Shader::unbind();

		//glEnable(GL_CULL_FACE);

	}
	
	////////////////////////////////////////////////////////
	
	FrameBuffer::bind(postProcessFrameBuffer);
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	vec3 cameraPosition = camera.getPosition();

	Shader::bind(&shader);

	Shader::currentShader->setUniformMatrix("V", &V[0][0]);
	Shader::currentShader->setUniformMatrix("P", &P[0][0]);
	Shader::currentShader->setUniform("cameraPosition_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);
	
	Texture::bind(shadowFrameBuffer->getTexture(), GL_TEXTURE0);
	Shader::currentShader->setUniform("shadowMap", 0);

	if (shadows) {
		Shader::currentShader->setUniformMatrix("DepthBiasVP", &depthBiasVP[0][0]);
		shadows = false;
	}

	Shader::currentShader->setUniform("lights[0].position_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);
	Shader::currentShader->setUniform("lights[0].color", 1.f, 0.f, 0.f);
	Shader::currentShader->setUniform("lights[0].power", 20.f);

	Shader::currentShader->setUniform("lights[1].position_worldspace", 0.f, 20.f, 5.f);
	Shader::currentShader->setUniform("lights[1].color", 0.f, 0.f, 1.f);
	Shader::currentShader->setUniform("lights[1].power", 50.f);

	Texture::bind(textures[1], GL_TEXTURE1);
	Shader::currentShader->setUniform("myTextureSampler", 1);

	for (int i = 0; i < 5; i++) {
		mat4 model = ModelView::getModelView(vec3(0, 0, i * 28), vec3(0, 0, 0), vec3(2, 2, 2));
		shShadowMap.setUniformMatrix("M", &model[0][0]);
		mesh[0]->render(GL_TRIANGLES);
	}

	Texture::bind(textures[0], GL_TEXTURE1);
	
	mat4 VP = P * V;
	for (auto it = entities.begin(), end = entities.end(); it != end; ++it) {
		(*it)->render(VP);
	}

	Texture::unbind(GL_TEXTURE1);
	Texture::unbind(GL_TEXTURE0);

	Shader::unbind();

	//

	Shader::bind(&skyShader);
	Shader::currentShader->setUniformMatrix("V", &V[0][0]);
	Shader::currentShader->setUniformMatrix("P", &P[0][0]);

	Texture::bind(&skyboxTexture, GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	Shader::currentShader->setUniform("cubeMapSampler", 0);

	mat4 M = ModelView::getModelView(cameraPosition);
	Shader::currentShader->setUniformMatrix("M", &M[0][0]);
	skybox.render();

	Texture::unbind(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	Shader::unbind();

	//

	window->pushGLStates();
	sf::CircleShape a(50.f);
	a.setFillColor(sf::Color::Red);
	window->draw(a);
	window->popGLStates();

	FrameBuffer::unbind();
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader::bind(&postProcessShader);
	Shader::currentShader->setUniform("renderedTexture", 0);
	Shader::currentShader->setUniform("time", wat += deltaTime.asSeconds()); //(float)deltaTime.asMicroseconds()
	//postProcessShader.setUniform("textureSize", window->getSize().x, window->getSize().y);
	
	Texture::bind(postProcessFrameBuffer->getTexture());
	PostProcess::render();
	Texture::unbind();

	Shader::unbind();

	window->display();

}

TestScene::~TestScene() {

	delete mesh[0]; mesh[0] = nullptr;
	delete mesh[1]; mesh[1] = nullptr;

	delete textures[0]; textures[0] = nullptr;
	delete textures[1]; textures[1] = nullptr;
	delete textures[2]; textures[2] = nullptr;

	delete shadowFrameBuffer; shadowFrameBuffer = nullptr;
	delete postProcessFrameBuffer; postProcessFrameBuffer = nullptr;

}