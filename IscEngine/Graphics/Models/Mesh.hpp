#pragma once

#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

#include "../Buffers/Buffers.hpp"
#include "../Shaders/Base/Shader.hpp"

namespace IscEngine {

	class Mesh {

		private:
			
			map<Shader*, VertexArray*> vertexArrays; // Each Shader has different Attribute positions :'(

			Buffer* vertexBuffer; // 0
			IndexBuffer* indexBuffer;
			Buffer* normalBuffer; // 1
			Buffer* textureBuffer; // 2
			Buffer* colorBuffer; // 3

		public:

			Mesh(const vector<float>& vertices);
			Mesh(const vector<vec3>& vertices);
			Mesh(Buffer* vertexBuffer);
			~Mesh();

			void addIndexes(const vector<unsigned short>& indexes);
			void addIndexes(const vector<unsigned int>& indexes);
			void addIndexBuffer(IndexBuffer* indexBuffer);

			void addNormals(const vector<float>& normals);
			void addNormals(const vector<vec3>& normals);
			void addNormalBuffer(Buffer* normalBuffer);

			void addUVs(const vector<float>& textureCoords);
			void addUVs(const vector<vec2>& textureCoords);
			void addUVBuffer(Buffer* textureBuffer);

			void addColors(const vector<float>& colors);
			void addColors(const vector<vec3>& colors);
			void addColorBuffer(Buffer* colorBuffer);

			VertexArray* cacheVertexArray(Shader* currentShader = Shader::currentShader);
			void render(const unsigned int type);

	};

}