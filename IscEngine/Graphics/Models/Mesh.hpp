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

	// Mesh
	class Mesh {

		private:
			
			map<Shader*, VertexArray*> vertexArrays; // Each Shader has different Attribute positions :'(

			Buffer* vertexBuffer;
			IndexBuffer* indexBuffer;
			Buffer* normalBuffer;
			Buffer* UVBuffer;
			Buffer* colorBuffer;

		public:

			// Creates the Mesh
			Mesh(const vector<float>& vertices);
			// Creates the Mesh
			Mesh(const vector<vec3>& vertices);
			// Creates the Mesh
			Mesh(Buffer* const vertexBuffer);
			// Destroys the Mesh
			~Mesh();

			// Adds the vertex indices
			void addIndices(const vector<unsigned short>& indices);
			// Adds the vertex indices
			void addIndices(const vector<unsigned int>& indices);
			// Adds the IndexBuffer
			void addIndexBuffer(IndexBuffer* const indexBuffer);

			// Adds the normals
			void addNormals(const vector<float>& normals);
			// Adds the normals
			void addNormals(const vector<vec3>& normals);
			// Adds the normal Buffer
			void addNormalBuffer(Buffer* const normalBuffer);

			// Adds the UVs
			void addUVs(const vector<float>& textureCoords);
			// Adds the UVs
			void addUVs(const vector<vec2>& textureCoords);
			// Adds the UV Buffer
			void addUVBuffer(Buffer* const textureBuffer);

			// Adds the Colors
			void addColors(const vector<float>& colors);
			// Adds the Colors
			void addColors(const vector<vec3>& colors);
			// Adds the Color Buffer
			void addColorBuffer(Buffer* const colorBuffer);

			// Returns the VAO for the Shader if exists. If not, creates and returns it
			VertexArray* cacheVertexArray(Shader* const currentShader = Shader::currentShader);
			// Renders the Mesh
			void render(const unsigned int type);

	};

}