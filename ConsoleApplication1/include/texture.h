#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <iostream>

class Texture {
    unsigned int id;
public:
    std::string path;
    std::string type;
    Texture() {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        this->id = textureID;
    }
    unsigned int getID() {
        return this->id;
    }
    void bind() {
        glBindTexture(GL_TEXTURE_2D, id);
    };
};
void activateTextureUnit(unsigned int id) {
    glActiveTexture(GL_TEXTURE0 + id);
}
class Texture2D : public Texture{
public:
    Texture2D(unsigned int width, unsigned int height) {
        // gen texture
        glBindTexture(GL_TEXTURE_2D, getID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture2D(std::string path) {
        // gen texture
        int width, height, nrComponents;
        unsigned char* data = stbi_load(path.data(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            this->bind();
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }
        std::cout << path.data() << std::endl;
        this->path = path;
        this->type = "";
    }
};