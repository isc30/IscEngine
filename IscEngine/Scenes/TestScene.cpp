#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Graphics/Shaders/Base/Shader.hpp"
#include "../Graphics/Buffers/Buffers.hpp"
#include "../Graphics/Models/Mesh.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Views/Modelview.hpp"

Shader* shader;
Camera camera;

std::vector<GLfloat> vertices = {

	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,

	1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 2.0f,
	1.0f, 1.0f, 2.0f,
	1.0f, 1.0f, 0.0f

};

std::vector<GLuint> indexes = {

	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4

};

std::vector<GLfloat> colors = {

	1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f

};

Mesh* mesh;

mat4 windowProjection;
mat4 Model;
mat4 MVP;

bool rotatingCamera = false;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	shader = new Shader();
	shader->loadFromFiles("../IscEngine/src/IscEngine/Graphics/Shaders/shader.vsh", "../IscEngine/src/IscEngine/Graphics/Shaders/shader.fsh");

	camera.setPosition(vec3(0, 2, 5));
	camera.lookAt(vec3(0, 2, 0));

	windowProjection = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 100.0f);

	vec3 position(0.0f, 2.0f, 0.0f);
	vec3 rotation(0.0f, 0.0f, 0.0f);
	vec3 scale(1.0f, 1.0f, 1.0f);

	Model = getModelView(position, rotation, scale);

	mesh = new Mesh(vertices);
	mesh->addIndexes(indexes);
	mesh->addColors(colors);

}

void TestScene::processEvent(sf::Event event) {

	switch (event.type) {

		case sf::Event::MouseButtonPressed:
			sf::Mouse::setPosition(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2), *this->window);
			break;

	}

}

void TestScene::update() {

	fpsCount++;
	fpsTime += deltaTime;
	if (fpsTime.asSeconds() >= 1) {

		cout << "Fps: " << fpsCount << endl;
		fpsTime -= sf::seconds(1);
		fpsCount = 0;

	}

	if (window->isFocused()) processInput();

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

		camera.setPosition(vec3(camera.getPosition().x + camera.getDirection().x * 2 * deltaTime.asSeconds(),
			camera.getPosition().y + camera.getDirection().y * 2 * deltaTime.asSeconds(),
			camera.getPosition().z + camera.getDirection().z * 2 * deltaTime.asSeconds()));

	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {

		camera.setPosition(vec3(camera.getPosition().x - camera.getDirection().x * 2 * deltaTime.asSeconds(),
			camera.getPosition().y - camera.getDirection().y * 2 * deltaTime.asSeconds(),
			camera.getPosition().z - camera.getDirection().z * 2 * deltaTime.asSeconds()));

	}

	MVP = windowProjection * camera.getView() * Model;

}

void TestScene::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(255, 0, 0);

	shader->bind();
	shader->setUniformMatrix("MVP", &MVP[0][0]);

	mesh->render(GL_TRIANGLES);

	shader->unbind();
	window->display();

}