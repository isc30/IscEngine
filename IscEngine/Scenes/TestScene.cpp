#include "TestScene.hpp"

using namespace IscEngine;
using namespace IscEngine::Scenes;

#include "../Utils/Log.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
#include "../Graphics/Buffers/Buffers.hpp"
#include "../Graphics/Models/Mesh.hpp"
#include "../Views/Cameras/Base/Camera.hpp"
#include "../Views/Modelview.hpp"

#include "../Graphics/Models/Loaders/ObjLoader.hpp"

Shader* shader;
Shader* shShadowMap;
Camera camera;

mat4 P;
mat4 V;

/////////////////////////////////

Mesh* mesh;

/////////////////////////////////

bool rotatingCamera = false;

GLuint textureId;
GLuint depthTexture;
GLuint FramebufferName;

int mapsize = 2;

TestScene::TestScene(Window* window) : Scene(window) {

	fpsCount = 0;
	fpsTime = sf::Time::Zero;

	shader = new Shader();
	shader->loadFromFiles(RESOURCE_PATH + "ShadowMapping_SimpleVersion.vertexshader", RESOURCE_PATH + "ShadowMapping_SimpleVersion.fragmentshader");

	shShadowMap = new Shader();
	shShadowMap->loadFromFiles(RESOURCE_PATH + "shShadowMap.vsh", RESOURCE_PATH + "shShadowMap.fsh");

	camera.setPosition(vec3(mapsize * 25 / 2 - 3, 10.5, mapsize * 25 / 2 - 3));
	camera.lookAt(vec3(0, 0, 0));

	P = glm::perspective(45.0f, window->getDefaultView().getSize().x / window->getDefaultView().getSize().y, 0.1f, 1000.0f);

	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUvs;
	std::vector<glm::vec3> objNormals;

	loadOBJ(RESOURCE_PATH + "room.obj", objVertices, objUvs, objNormals);

	std::vector<unsigned int> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	//indexVBO(objVertices, objUvs, objNormals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	std::vector<GLfloat> vertices;
	for (int i = 0; i < objVertices.size(); i++) {
		vertices.push_back(objVertices.at(i).x);
		vertices.push_back(objVertices.at(i).y);
		vertices.push_back(objVertices.at(i).z);
	}

	std::vector<GLfloat> normals;
	for (int i = 0; i < objNormals.size(); i++) {
		normals.push_back(objNormals.at(i).x);
		normals.push_back(objNormals.at(i).y);
		normals.push_back(objNormals.at(i).z);
	}

	std::vector<GLfloat> texture;
	for (int i = 0; i < objUvs.size(); i++) {
		texture.push_back(objUvs.at(i).x);
		texture.push_back(objUvs.at(i).y);
	}

	Log::cout << "Vertices: " << vertices.size() / 3 << endl;

	mesh = new Mesh(vertices);
	//mesh->addIndexes(indices);
	mesh->addNormals(normals);
	mesh->addTextureCoords(texture);

	GLuint textureGl;
	sf::Image image;

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

		textureId = textureGl;

	}

	///////////////////////////////////////////////////////

	FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	// We dont want color, only depth
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Log::cout << "Error framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // End framebuffer

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

void TestScene::render() {

	// Render to texture
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0, 0, 2048, 2048);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, window->getSize().x, window->getSize().y);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shShadowMap->bind();

	int size = 30;
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-size, size, -size, size, -size * 10, size * 10);
	//glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50000.0f);
	glm::mat4 depthViewMatrix = glm::lookAt(vec3(20, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	shShadowMap->setUniformMatrix("V", &depthViewMatrix[0][0]);
	shShadowMap->setUniformMatrix("P", &depthProjectionMatrix[0][0]);

	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			mat4 model = glm::translate(vec3(i * 25, 2.0f, j * 25));
			model = glm::rotate(model, radians(i * 25.f + j * 25.f), glm::vec3(0, 1, 0));
			shShadowMap->setUniformMatrix("M", &model[0][0]);
			mesh->render(GL_TRIANGLES);
		}
	}

	shShadowMap->unbind();

	glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasVP = biasMatrix * depthVP;
	
	///////////////////////////////////////-

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();
	shader->setUniformMatrix("V", &V[0][0]);
	shader->setUniformMatrix("P", &P[0][0]);
	vec3 cameraPosition = camera.getPosition();
	shader->setUniform("LightPosition_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	shader->setUniform("myTextureSampler", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	shader->setUniform("shadowMap", 1);

	shader->setUniformMatrix("DepthBiasVP", &depthBiasVP[0][0]);

	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			mat4 model = glm::translate(vec3(i * 25, 2.0f, j * 25));
			model = glm::rotate(model, radians(i * 25.f + j * 25.f), glm::vec3(0, 1, 0));
			shader->setUniformMatrix("M", &model[0][0]);
			mesh->render(GL_TRIANGLES);
		}
	}

	shader->unbind();
	//*/

	window->display();

}