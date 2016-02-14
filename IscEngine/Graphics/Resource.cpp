#include "Resource.hpp"
#include "../Utils/Log.hpp"

#include "Textures/Texture.hpp"
#include "Models/Loaders/ObjLoader.hpp"
#include "Models/Mesh.hpp"
#include "Shaders/Base/Shader.hpp"

using namespace IscEngine;

const string Resource::RESOURCE_PATH = "../IscEngine/IscEngine/Resources/";
const string Resource::ERROR_TEXTURE = "error.png";

namespace IscEngine {

    template<>
    Texture* Resource::load<Texture*>(const char* fileName) {

        Texture* texture = new Texture();
        if (!texture->loadFromFile(Resource::RESOURCE_PATH + "Textures/" + fileName)) {
            Log::cout << "Texture loading error (" << fileName << ")" << endl;
            texture->loadFromFile(Resource::RESOURCE_PATH + "Textures/" + Resource::ERROR_TEXTURE);
        }
        return texture;

    }

    template<>
    Mesh* Resource::load<Mesh*>(const char* fileName) {

        vector<unsigned int> objIndices;
        std::vector<glm::vec3> objVertices;
        std::vector<glm::vec2> objUvs;
        std::vector<glm::vec3> objNormals;
        loadModel(Resource::RESOURCE_PATH + "Models/" + fileName, objIndices, objVertices, objUvs, objNormals);

        Mesh* mesh = new Mesh(objVertices);
        if (objIndices.size() > 0) mesh->addIndices(objIndices);
        if (objNormals.size() > 0) mesh->addNormals(objNormals);
        if (objUvs.size() > 0) mesh->addUVs(objUvs);

        return mesh;

    }

    template<>
    Shader* Resource::load<Shader*>(const char* vertexFileName, const char* fragmentFileName) {

        Shader* shader = new Shader();
        shader->loadFromFiles(Resource::RESOURCE_PATH + "Shaders/" + vertexFileName, Resource::RESOURCE_PATH + "Shaders/" + fragmentFileName);
        return shader;

    }

}
