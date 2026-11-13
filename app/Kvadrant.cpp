#include "Kvadrant.hpp"

Kvadrant::Kvadrant(glm::vec2 offset, glm::vec3 color) : offset(offset), color(color) {}

void Kvadrant::setColor(const glm::vec3 &c) {
    color = c;
}

glm::vec3 Kvadrant::getColor() const {
    return color;
}

glm::vec2 Kvadrant::getOffset() const {
    return offset;
}