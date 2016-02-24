#pragma once

#include "../Engine.hpp"

#include "Base/Scene.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
#include "../Graphics/Models/Mesh.hpp"
#include "../World/Entities/StaticEntity.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Graphics/Textures/Texture.hpp"
#include "../World/SkyBox.hpp"
#include "../Graphics/Renderers/Simple3D.hpp"
#include "../Utils/Log.hpp"

namespace IscEngine { namespace Scenes {

	class TestScene : public Scene {

		private:

			unsigned int fpsCount;
			sf::Time fpsTime;
			Shader shader, shShadowMap, postProcessShader;
			Mesh* mesh[3];
			Texture* textures[3];
			Shader skyShader;
            SkyBox skybox;
            Texture skyboxTexture;
			FrameBuffer* shadowFrameBuffer, *postProcessFrameBuffer;
			Renderers::Simple3D* simpleRenderer;
			vector<StaticEntity*> entities;

		public:

			TestScene(Window* window);
			~TestScene();

			void processEvent(const sf::Event& event);

			void update();
			void processInput();
			void render();

	};

} }
