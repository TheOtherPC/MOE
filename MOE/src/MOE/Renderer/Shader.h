//
// Created by gru on 1/14/24.
//

#ifndef MOE_SHADER_H
#define MOE_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace MOE {
    class Shader {
    public:
        unsigned int ID;

        Shader(const char *vertexPath, const char *fragmentPath);
//        ~Shader(); // Dont know if needed
        void use();

        void set(const std::string &name, bool value) const;

        void set(const std::string &name, int value) const;

        void set(const std::string &name, float value) const;

        void set(const std::string &name, glm::mat4 value) const;

        void clear();

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    };

}
#endif //MOE_SHADER_H
