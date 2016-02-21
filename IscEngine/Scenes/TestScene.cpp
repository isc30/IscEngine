#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Graphics/Resource.hpp"
#include "../Graphics/Models/Loaders/ObjLoader.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Views/Modelview.hpp"
#include "../Graphics/Shaders/PostProcess.hpp"
#include "../World/SkyBox.hpp"
#include "../Graphics/Renderers/Simple3D.hpp"

Camera camera;

mat4 P;
mat4 V;

bool rotatingCamera = false;

int mapsize = 1;
float separation = 5.f;

Shader skyShader;
SkyBox skybox;
Texture skyboxTexture;

Renderers::Simple3D* simpleRenderer;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

    shader = *Resource::load<Shader>("Simple3D.vsh", "Simple3D.fsh");
	shShadowMap = *Resource::load<Shader>("shadowMapper.vsh", "shadowMapper.fsh");
	postProcessShader = *Resource::load<Shader>("postProcess.vsh", "postProcess.fsh");

	camera.setPosition(vec3(mapsize * separation / 2 - 3, 30, mapsize * separation / 2 + 25));
	camera.lookAt(vec3(0, 20, 0));

	P = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 1000.0f);

	mesh[0] = Resource::load<Mesh>("fbx_PuenteRomano.fbx");
	mesh[1] = Resource::load<Mesh>("katarina.obj");
	mesh[2] = Resource::load<Mesh>("katarina_low.obj");

	simpleRenderer = new Renderers::Simple3D();

	// Create StaticEntities
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			StaticEntity* entity = new StaticEntity(mesh[1]);
			entity->addMesh(50, mesh[2]);
			entity->setPosition(vec3(i * separation, 18.3f, j * separation));
			entity->setRotation(vec3(0, radians(i * 25.f + j * 25.f), 0));
			entities.push_back(entity);
			//simpleRenderer->addEntity(entity);
		}
	}

    textures[0] = Resource::load<Texture>("katarina_base_diffuse.png");
    textures[1] = Resource::load<Texture>("PiedraRomano_Difuse.jpg");

	///////////////////////////////////////////////////////

    skyShader = *Resource::load<Shader>("SkyBox.vsh", "SkyBox.fsh");
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
			if (event.key.code == sf::Keyboard::B) this->endScene(new Scenes::TestScene(window));
			if (event.key.code == sf::Keyboard::Y) {
				if (entities.size() > 0) {
					delete entities.back();
					entities.pop_back();
				}
			}
			if (event.key.code == sf::Keyboard::U) {
				StaticEntity* entity = new StaticEntity(mesh[1]);
				entity->addMesh(50, mesh[2]);
				entity->setPosition(vec3(entities.size() * separation, 18.3f, entities.size() * separation));
				entity->setRotation(vec3(0, radians(entities.size() * 25.f + entities.size() * 25.f), 0));
				entities.push_back(entity);
			}
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

	/*for (auto it = entities.begin(), end = entities.end(); it != end; ++it) {

		vec3 currentRotation = (*it)->getRotation();
		currentRotation.y += radians(45.f * deltaTime.asSeconds());
		(*it)->setRotation(currentRotation);

	}*/

}

void TestScene::processInput() {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		float sensibilidad = 0.15f;

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		camera.setPosition(vec3(camera.getPosition().x + camera.getDirection().x * 20 * deltaTime.asSeconds(),
								camera.getPosition().y + camera.getDirection().y * 20 * deltaTime.asSeconds(),
								camera.getPosition().z + camera.getDirection().z * 20 * deltaTime.asSeconds()));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		camera.setPosition(vec3(camera.getPosition().x - camera.getDirection().x * 20 * deltaTime.asSeconds(),
								camera.getPosition().y - camera.getDirection().y * 20 * deltaTime.asSeconds(),
								camera.getPosition().z - camera.getDirection().z * 20 * deltaTime.asSeconds()));

	}

	//Try moving katarina
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

        vec3 newRotation = entities.at(0)->getRotation() + vec3(0, radians(135 * deltaTime.asSeconds()), 0);
        entities.at(0)->setRotation(newRotation);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

        vec3 newRotation = entities.at(0)->getRotation() - vec3(0, radians(135 * deltaTime.asSeconds()), 0);
        entities.at(0)->setRotation(newRotation);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

        vec3 frontDirection = normalize(vec3(entities.at(0)->getModelMatrix() * vec4(0, 0, 1, 0)));
        vec3 newPosition = entities.at(0)->getPosition() + frontDirection * (5 * deltaTime.asSeconds());
        entities.at(0)->setPosition(newPosition);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		vec3 frontDirection = normalize(vec3(entities.at(0)->getModelMatrix() * vec4(0, 0, 1, 0)));
        vec3 newPosition = entities.at(0)->getPosition() - frontDirection * (5 * deltaTime.asSeconds());
        entities.at(0)->setPosition(newPosition);

	}

}

bool moveRight = false;
float pos = 20;

float wat = 0;

void TestScene::render() {

	simpleRenderer->lightSetup.clear();
	simpleRenderer->clearEntities();
	simpleRenderer->addEntities(entities);

	FrameBuffer::bind(postProcessFrameBuffer);
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3 cameraPosition = camera.getPosition();

	Shader::bind(&shader);

	Texture::bind(shadowFrameBuffer->getTexture(), 0);
	Shader::currentShader->setUniform("shadowMap", 0);

	LightSource l0;
	l0.position = cameraPosition;
	l0.color = vec3(1.f, 1.f, 1.f);
	l0.power = 15.f;
	simpleRenderer->lightSetup.add(&l0);

	LightSource l1;
	l1.position = vec3(0.f, 20.f, 5.f);
	l1.color = vec3(0.f, 0.f, 1.f);
	l1.power = 20.f;
	simpleRenderer->lightSetup.add(&l1);

	LightSource l2;
	l2.position = vec3(0.f, 20.f, 40.f);
	l2.color = vec3(0.f, 1.f, 0.f);
	l2.power = 20.f;
	simpleRenderer->lightSetup.add(&l2);

	LightSource l3;
	l3.position = vec3(0.f, 20.f, 80.f);
	l3.color = vec3(1.f, 0.5f, 0.5f);
	l3.power = 20.f;
	simpleRenderer->lightSetup.add(&l3);

	Texture::bind(textures[1], 1);
	Shader::currentShader->setUniform("myTextureSampler", 1);

	for (int i = 0; i < 5; i++) {
		mat4 model = ModelView::getModelView(vec3(0, 0, i * 28), vec3(0, 0, 0), vec3(2, 2, 2));
		shShadowMap.setUniformMatrix("M", &model[0][0]);
		mesh[0]->render(GL_TRIANGLES);
	}

	Texture::bind(textures[0], 1);
	
	simpleRenderer->render(P, &camera);

	Texture::unbind(1);
	Texture::unbind(0);

	Shader::unbind();

	//

	Shader::bind(&skyShader);
	Shader::currentShader->setUniformMatrix("V", &V[0][0]);
	Shader::currentShader->setUniformMatrix("P", &P[0][0]);

	Texture::bind(&skyboxTexture, 0, GL_TEXTURE_CUBE_MAP);
	Shader::currentShader->setUniform("cubeMapSampler", 0);

	mat4 M = ModelView::getModelView(cameraPosition);
	Shader::currentShader->setUniformMatrix("M", &M[0][0]);
	skybox.render();

	Texture::unbind(0, GL_TEXTURE_CUBE_MAP);
	Shader::unbind();

	//

	window->pushGLStates();
	sf::CircleShape a(25.f);
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

	Texture::bind(postProcessFrameBuffer->getTexture(), 0);
	PostProcess::render();
	Texture::unbind(0);

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
