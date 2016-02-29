#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Graphics/Resource.hpp"
#include "../Graphics/Models/Loaders/ObjLoader.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Views/Modelview.hpp"
#include "../Graphics/Shaders/PostProcess.hpp"
#include "../Graphics/Materials/Material.hpp"
#include "../Graphics/Models/Model.hpp"

Camera camera;

mat4 P;
mat4 V;

bool rotatingCamera = false;

int mapsize = 1;
float separation = 5.f;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	shShadowMap = *Resource::load<Shader>("shadowMapper.vsh", "shadowMapper.fsh");
	postProcessShader = *Resource::load<Shader>("postProcess.vsh", "postProcess.fsh");

	camera.setPosition(vec3(mapsize * separation / 2 - 3, 30, mapsize * separation / 2 + 25));
	camera.lookAt(vec3(0, 20, 0));

	P = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 1000.0f);

	simpleRenderer = new Renderers::Simple3D();

	///////// MODEL

	Mesh* katarinaMeshFull = Resource::load<Mesh>("katarina.obj");
	Mesh* katarinaMeshLow = Resource::load<Mesh>("katarina_low.obj");
	Texture* katarinaDiffuse = Resource::load<Texture>("katarina_base_diffuse.png");
	Texture* katarinaSpecular = Resource::load<Texture>("katarina_base_specular.png");

	// Katarina
	Model* katarinaModelHD = new Model();
	katarinaModelHD->mesh = katarinaMeshFull; // HD
	katarinaModelHD->material = new Material();
	katarinaModelHD->material->diffuseMap = katarinaDiffuse;
	katarinaModelHD->material->specularMap = katarinaSpecular;

	Model* katarinaModelLow = new Model();
	katarinaModelLow->mesh = katarinaMeshLow; // Low poly
	katarinaModelLow->material = new Material();
	katarinaModelLow->material->diffuseMap = katarinaDiffuse;
	//katarinaModelLow->material->specularMap = katarinaSpecular;

	// Sphere
	Model* sphereModel = new Model();
	sphereModel->mesh = Resource::load<Mesh>("sphere.fbx");
	sphereModel->material = new Material();
	sphereModel->material->diffuseMap = Resource::load<Texture>("d.jpg");;
	sphereModel->material->specularMap = Resource::load<Texture>("s.jpg");
	sphereModel->material->materialProperties.shininess = 10.f;

	// Puente
	Model* puenteModel = new Model();
	puenteModel->mesh = Resource::load<Mesh>("fbx_PuenteRomano.fbx");;
	puenteModel->material = new Material();
	puenteModel->material->diffuseMap = Resource::load<Texture>("PiedraRomano_Difuse.jpg");
	puenteModel->material->specularMap = Resource::load<Texture>("piedra_specular.png");
	puenteModel->material->materialProperties.shininess = 50.f;

	////////

	// Create StaticEntities
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			StaticEntity* entity = new StaticEntity(katarinaModelHD);
			entity->addModel(50, katarinaModelLow);
			entity->setPosition(vec3(i * separation, 18.3f, j * separation));
			entity->setRotation(vec3(0, radians(i * 25.f + j * 25.f), 0));
			entities.push_back(entity);
		}
	}

	for (int i = 0; i < 5; i++) {

		StaticEntity* entity = new StaticEntity(puenteModel);
		entity->setPosition(vec3(0, 0, i * 28));
		entity->setScale(vec3(2, 2, 2));
		entities.push_back(entity);

	}

	// Sphere
	StaticEntity* entity = new StaticEntity(sphereModel);
	entity->setPosition(vec3(0, 22.3f, 60));
	entity->setScale(vec3(2, 2, 2));
	entities.push_back(entity);

	///////////////////////////////////////////////////////

    skyShader = *Resource::load<Shader>("SkyBox.vsh", "SkyBox.fsh");
	skyboxTexture.loadCubeMap(vector<string>({
		Resource::RESOURCE_PATH + "Textures/SkyBox/right.jpg",
		Resource::RESOURCE_PATH + "Textures/SkyBox/left.jpg",
		Resource::RESOURCE_PATH + "Textures/SkyBox/top.jpg",
		Resource::RESOURCE_PATH + "Textures/SkyBox/bottom.jpg",
		Resource::RESOURCE_PATH + "Textures/SkyBox/back.jpg",
		Resource::RESOURCE_PATH + "Textures/SkyBox/front.jpg"
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

	StaticEntity* mikey = entities.at(entities.size() - 1);
	vec3 currentRotation = mikey->getRotation();
	currentRotation.y += radians(45.f * deltaTime.asSeconds());
	mikey->setRotation(currentRotation);

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

	vec3 cameraPosition = camera.getPosition();

	LightSource l0;
	l0.position = cameraPosition;
	l0.color = vec3(1.f, 1.f, 1.f);
	l0.power = 5.f;
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

	FrameBuffer::bind(postProcessFrameBuffer);
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	simpleRenderer->render(P, &camera);

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
	Shader::currentShader->setUniform("textureSize", (float)window->getSize().x, (float)window->getSize().y);

	Texture::bind(postProcessFrameBuffer->getTexture(), 0);
	PostProcess::render();
	Texture::unbind(0);

	Shader::unbind();

	window->display();

}

TestScene::~TestScene() {



}