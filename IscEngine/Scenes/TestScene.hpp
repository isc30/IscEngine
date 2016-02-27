#pragma once

#include "../Engine.hpp"

#include "Base/Scene.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
#include "../Graphics/Models/Mesh.hpp"
#include "../World/Entities/StaticEntity.hpp"
#include "../Graphics/Buffers/FrameBuffer.hpp"
#include "../Graphics/Textures/Texture.hpp"
#include "../Graphics/Renderers/Simple3D.hpp"
#include "../World/SkyBox.hpp"
#include "../Utils/Log.hpp"

namespace IscEngine { namespace Scenes {

	class TestScene : public Scene {

		private:

			unsigned int fpsCount;
			sf::Time fpsTime;
			Shader shShadowMap, postProcessShader;
			Shader skyShader;
			SkyBox skybox;
			Texture skyboxTexture;
			Renderers::Simple3D* simpleRenderer;
			FrameBuffer* shadowFrameBuffer, *postProcessFrameBuffer;
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