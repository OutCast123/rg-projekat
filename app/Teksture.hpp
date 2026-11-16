#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
    explicit Texture(const std::string &path);
    ~Texture();

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;

    void bind(unsigned int unit = 0) const;
    void setFilter(GLint filter);
    bool isValid() const { return ID != 0; }

    unsigned int ID = 0;
};