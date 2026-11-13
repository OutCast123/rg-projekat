#pragma once

#include <glm/glm.hpp>

class Kvadrant {
public:
    Kvadrant(glm::vec2 offset, glm::vec3 color);

    void setColor(const glm::vec3 &c);
    glm::vec3 getColor() const;
    glm::vec2 getOffset() const;

private:
    glm::vec2 offset;
    glm::vec3 color;
};