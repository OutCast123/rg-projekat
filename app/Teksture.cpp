#include "Teksture.hpp"

#include <iostream>
#include <stb_image.h>

Texture::Texture(const std::string &path) {
    stbi_set_flip_vertically_on_load(true);

    int width = 0, height = 0, channels = 0;
    
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if (!data) {
        std::cout << "ERROR::TEXTURE::LOAD_FAILED: " << path << std::endl;
        return;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture() {
    if (ID != 0) {
        glDeleteTextures(1, &ID);
    }
}

Texture::Texture(Texture &&other) noexcept : ID(other.ID) {
    other.ID = 0;
}

Texture &Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        if (ID != 0) glDeleteTextures(1, &ID);
        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::setFilter(GLint filter) {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}