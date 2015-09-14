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
	1.0f, 1.0f, 0.0f,

	-1.0f, -1.0f, 2.0f,
	1.0f, -1.0f, 2.0f,
	1.0f, 1.0f, 2.0f,
	-1.0f, 1.0f, 2.0f,

};

std::vector<GLuint> indexes = {

	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8

};

std::vector<GLfloat> texture = {

	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,

	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,

	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f

};

mat4 windowProjection;
mat4 VP;

/////////////////////////////////

std::vector<GLfloat> allVertices;
std::vector<GLuint> allIndexes;
std::vector<GLfloat> allTextures;

Mesh* mesh;

/////////////////////////////////

bool rotatingCamera = false;

GLuint textureId;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	shader = new Shader();
	shader->loadFromFiles("shader.vsh", "shader.fsh");

	camera.setPosition(vec3(148 * 5, 25, 148 * 5));
	camera.lookAt(vec3(0, 2, 0));

	windowProjection = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 10000.0f);

	for (int i = 0; i < 300; i++) {

		for (int j = 0; j < 300; j++) {

			vec3 position(i * 5, 2.0f, j * 5);

			////////////////////////////////////////////////////////////////////////////////////////
			for (int k = 0; k < vertices.size(); k += 3) {

				allVertices.push_back(vertices.at(k) + position.x);
				allVertices.push_back(vertices.at(k + 1) + position.y);
				allVertices.push_back(vertices.at(k + 2) + position.z);

			}

			for (int k = 0; k < indexes.size(); k += 6) {

				int offset = allIndexes.size() / 6 * 4;
				allIndexes.push_back(offset); allIndexes.push_back(offset + 1); allIndexes.push_back(offset + 2);
				allIndexes.push_back(offset + 2); allIndexes.push_back(offset + 3); allIndexes.push_back(offset);

			}

			for (int k = 0; k < texture.size(); k++) {

				allTextures.push_back(texture.at(k));

			}

		}

	}

	mesh = new Mesh(allVertices);
	mesh->addIndexes(allIndexes);
	mesh->addTextureCoords(allTextures);

	GLuint texture;
	sf::Image image;

	if (!image.loadFromFile("textura.png")) {

		std::cout << "Texture loading error" << std::endl;

	} else {

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,  //mip-map level
			GL_RGBA, //We want the internal texture to have RGBA components
			image.getSize().x, image.getSize().y,// size of texture
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

		textureId = texture;

	}

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

	VP = windowProjection * camera.getView();

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

void TestScene::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(255, 0, 0);

	mat4 model(1.0f);

	glBindTexture(GL_TEXTURE_2D, textureId);

	shader->bind();
	shader->setUniformMatrix("VP", &VP[0][0]);
	shader->setUniformMatrix("M", &model[0][0]);

	mesh->render(GL_TRIANGLES);

	shader->unbind();
	window->display();

}