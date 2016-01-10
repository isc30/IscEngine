#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

#include "../Buffers/Buffers.hpp"

namespace IscEngine {

	class Mesh {

		private:

			VertexArray* vertexArray;

			Buffer* vertexBuffer; // 0
			IndexBuffer* indexBuffer;
			Buffer* normalBuffer; // 1
			Buffer* textureBuffer; // 2
			Buffer* colorBuffer; // 3

		public:

			Mesh(vector<float> vertices);
			Mesh(vector<vec3> vertices);
			Mesh(Buffer* vertexBuffer);
			~Mesh();

			void addIndexes(vector<GLuint> indexes);
			void addIndexes(vector<vec3> indexes);
			void addIndexBuffer(IndexBuffer* indexBuffer);

			void addNormals(vector<float> normals);
			void addNormalBuffer(Buffer* normalBuffer);

			void addTextureCoords(vector<float> textureCoords);
			void addTextureBuffer(Buffer* textureBuffer);

			void addColors(vector<float> colors);
			void addColorBuffer(Buffer* colorBuffer);

			void render(GLenum type);

	};

}