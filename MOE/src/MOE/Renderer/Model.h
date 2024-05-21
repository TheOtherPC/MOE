//
// Created by gru on 1/29/24.
//

#ifndef MOE_MODEL_H
#define MOE_MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

namespace MOE {
//    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
//    unsigned int TextureFromFile(const char *path, const std::string &directory, bool inverted, bool gamma = false);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool inverted);

    class Model {
    public:
        std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

//        Model(std::string const &path, bool gamma = false);
        Model(std::string const &path, bool inverted, bool gamma = false);
        Model(std::string const &path, bool inverted, glm::vec3 s, bool gamma = false);

        void draw(Shader &shader);
        std::pair<glm::vec3, glm::vec3> boundingBox;

    private:
        const aiScene* scene;
        bool flipTextures;
        glm::vec3 scale;
        void loadModel(std::string const &path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}

#endif //MOE_MODEL_H
